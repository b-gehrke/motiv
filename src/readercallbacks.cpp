#include "readercallbacks.hpp"
#include "src/models/communication/communication.hpp"
#include "src/models/slot.hpp"
#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "src/models/communication/blockingsendevent.hpp"
#include "src/models/communication/blockingreceiveevent.hpp"
#include "src/models/communication/nonblockingsendevent.hpp"
#include <QStringListModel>
#include <memory>
#include <utility>
#include <type_traits>

ReaderCallbacks::ReaderCallbacks(otf2::reader::reader &rdr) :
    rdr_(rdr),
    slots_(std::vector<Slot*>()),
    communications_(std::vector<Communication*>()),
    collectiveCommunications_(std::vector<CollectiveCommunicationEvent*>()),
    slotsBuilding(),
    program_start_() {

}


std::vector<Slot*> ReaderCallbacks::getSlots() {
    return this->slots_;
}

otf2::chrono::duration ReaderCallbacks::duration() const {
    return this->program_end_ - this->program_start_;
}

void ReaderCallbacks::definition(const otf2::definition::location &loc) {
    rdr_.register_location(loc);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::program_begin &event) {
    this->program_start_ = event.timestamp();
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::program_end &event) {
    this->program_end_ = event.timestamp();
}


void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::enter &event) {
    auto start = event.timestamp() - this->program_start_;

    Slot::Builder builder{};
    auto region = new otf2::definition::region(event.region());
    auto location = new otf2::definition::location(loc);
    builder.start(start)->location(location)->region(region);

    std::vector<Slot::Builder> *builders;
    auto buildersIt = this->slotsBuilding.find(location->ref().get());
    if (buildersIt == this->slotsBuilding.end()) {
        builders = new std::vector<Slot::Builder>();
        this->slotsBuilding.insert({location->ref().get(), builders});
    } else {
        builders = buildersIt->second;
    }

    builders->push_back(builder);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::leave &event) {
    auto builders = this->slotsBuilding.at(location.ref().get());

    Slot::Builder &builder = builders->back();

    auto end = event.timestamp() - this->program_start_;
    builder.end(end);

    this->slots_.push_back(new Slot(builder.build()));

    builders->pop_back();
}


template<typename T>
void ReaderCallbacks::communicationEvent(T* self, uint32_t matching,
                                         std::map<uint32_t, std::vector<CommunicationEvent*> *> &selfPending,
                                         std::map<uint32_t, std::vector<CommunicationEvent*> *> &matchingPending
) {
    // Check for a pending matching call
    if (matchingPending.contains(matching)) {
        auto& matchingEvents = matchingPending[matching];
        auto matchingEvent = matchingEvents->back();

        auto communication = new Communication(matchingEvent, self);
        communications_.push_back(communication);

        matchingEvents->pop_back();
        if (matchingEvents->empty()) {
            delete matchingEvents;
            matchingPending.erase(matching);
        }
    } else {
        std::vector<CommunicationEvent*> *matchingEvents;
        auto id = self->getLocation()->ref().get();
        if (selfPending.contains(id)) {
            matchingEvents = selfPending[id];
        } else {
            matchingEvents = new std::vector<CommunicationEvent*>();
            selfPending[id] = matchingEvents;
        }

        matchingEvents->push_back(self);
    }
}

void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::mpi_send &send) {
    auto location = new otf2::definition::location(loc);
    auto comm = new types::communicator(send.comm());
    auto ev = new BlockingSendEvent(relative(send.timestamp()), location, comm);

    this->communicationEvent<BlockingSendEvent>(ev, send.receiver(), pendingSends, pendingReceives);
}

void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::mpi_receive &receive) {
    auto location = new otf2::definition::location(loc);
    auto comm = new types::communicator(receive.comm());
    auto ev = new BlockingReceiveEvent(relative(receive.timestamp()), location, comm);

    this->communicationEvent(ev, receive.sender(), pendingReceives, pendingSends);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_isend_request &request) {
    NonBlockingSendEvent::Builder builder;
    auto comm = new types::communicator (request.comm());
    auto loc = new otf2::definition::location(location);
    auto start = relative(request.timestamp());
    auto receiver = request.receiver();
    builder.communicator(comm);
    builder.location(loc);
    builder.start(start);
    builder.receiver(receiver);

    this->uncompletedRequests.insert({request.request_id(), builder});
}

void
ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_isend_complete &complete) {
    if (!uncompletedRequests.contains(complete.request_id())) {
        throw std::logic_error("Found a mpi_isend_complete event with no matching mpi_isend_request event!");
    }

    auto builderVariant = uncompletedRequests[complete.request_id()];
    if(!holds_alternative<NonBlockingSendEvent::Builder>(builderVariant)) {
        throw std::logic_error("mpi_isend_complete event completes an mpi_ireceive event!");
    }
    
    auto builder = get<NonBlockingSendEvent::Builder>(builderVariant);

    auto end = relative(complete.timestamp());
    builder.end(end);

    auto ev = new NonBlockingSendEvent(builder.build());

    communicationEvent(ev, builder.receiver(), pendingSends, pendingReceives);
}

void
ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_ireceive_complete &complete) {
    if (!uncompletedRequests.contains(complete.request_id())) {
        throw std::logic_error("Found a mpi_ireceive_complete event with no matching mpi_ireceive_request event!");
    }

    auto builderVariant = uncompletedRequests[complete.request_id()];
    if(!holds_alternative<NonBlockingReceiveEvent::Builder>(builderVariant)) {
        throw std::logic_error("mpi_ireceive_complete event completes an mpi_isend event!");
    }

    auto builder = get<NonBlockingReceiveEvent::Builder>(builderVariant);

    auto end = relative(complete.timestamp());
    builder.end(end);

    auto ev = new NonBlockingReceiveEvent(builder.build());

    communicationEvent(ev, builder.sender(), pendingReceives, pendingSends);
}

void
ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_ireceive_request &request) {

    NonBlockingReceiveEvent::Builder builder;
    auto comm = new types::communicator (request.comm());
    auto loc = new otf2::definition::location(location);
    auto start = relative(request.timestamp());
    auto sender = request.sender();
    builder.communicator(comm);
    builder.location(loc);
    builder.start(start);
    builder.sender(sender);

    this->uncompletedRequests.insert({request.request_id(), builder});
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_request_test &test) {
    callback::event(location, test);
}

void ReaderCallbacks::event(const otf2::definition::location &location,
                            const otf2::event::mpi_request_cancelled &cancelled) {
    callback::event(location, cancelled);
}

void
ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_collective_begin &begin) {
    CollectiveCommunicationEvent::Member::Builder builder;
    auto loc = new otf2::definition::location(location);
    auto start = relative(begin.timestamp());
    
    builder.location(loc);
    builder.start(start);
    
    this->ongoingCollectiveCommunicationMembers.insert({loc->ref().get(), builder});
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_collective_end &anEnd) {
    if(ongoingCollectiveCommunication == nullptr) {
        ongoingCollectiveCommunication = new CollectiveCommunicationEvent::Builder();
        std::vector<CollectiveCommunicationEvent::Member*> members;
        auto loc = new otf2::definition::location( location);
        auto comm = new types::communicator (anEnd.comm());
        auto operation = anEnd.type();
        auto root = anEnd.root();
        ongoingCollectiveCommunication->members(members);
        ongoingCollectiveCommunication->location(loc);
        ongoingCollectiveCommunication->communicator(comm);
        ongoingCollectiveCommunication->operation(operation);
        ongoingCollectiveCommunication->root(root);
    }

    auto member = ongoingCollectiveCommunicationMembers[location.ref().get()];
    auto end = relative(anEnd.timestamp());
    member.end(end);

    ongoingCollectiveCommunication->members()->push_back(new CollectiveCommunicationEvent::Member(member.build()));
    ongoingCollectiveCommunicationMembers.erase(location.ref().get());

    // If the map is now empty, all ranks have completed the collective operation and the communication event can be build
    if(ongoingCollectiveCommunicationMembers.empty()){
        auto event = new CollectiveCommunicationEvent(ongoingCollectiveCommunication->build());
        collectiveCommunications_.push_back(event);
        delete ongoingCollectiveCommunication;
        ongoingCollectiveCommunication = nullptr;
    }
}


void ReaderCallbacks::events_done(const otf2::reader::reader &) {
    std::sort(this->slots_.begin(), this->slots_.end(), [](Slot *rhs, Slot *lhs) {
        return rhs->start < lhs->start;
    });
    std::sort(this->communications_.begin(), this->communications_.end(),
              [](Communication *rhs, Communication *lhs) {
                  return rhs->getStart()->getStart() < lhs->getStart()->getStart();
              });

    for (const auto &item: this->slotsBuilding) {
        // TODO: Warn about uncomplete slots
        delete item.second;
    }
    for (const auto &item: this->pendingSends) {
        // TODO: Warn about unmatched sends
        delete item.second;
    }
    for (const auto &item: this->pendingReceives) {
        // TODO: Warn about unmatched receives
        delete item.second;
    }
    for(const auto &item: this->uncompletedRequests) {
        // TODO: Warn about uncompleted (and not cancelled) requests
    }

    std::destroy(this->slotsBuilding.begin(), this->slotsBuilding.end());
    std::destroy(this->pendingSends.begin(), this->pendingSends.end());
    std::destroy(this->pendingReceives.begin(), this->pendingReceives.end());
    std::destroy(this->uncompletedRequests.begin(), this->uncompletedRequests.end());
}

otf2::chrono::duration ReaderCallbacks::relative(otf2::chrono::time_point timepoint) const {
    return timepoint - program_start_;
}

std::vector<Communication*> ReaderCallbacks::getCommunications() {
    return communications_;
}

std::vector<CollectiveCommunicationEvent*> ReaderCallbacks::getCollectiveCommunications() {
    return collectiveCommunications_;
}
