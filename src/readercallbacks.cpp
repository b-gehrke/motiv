#include "readercallbacks.hpp"
#include "src/models/communication.hpp"
#include "src/models/slot.hpp"
#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include <QStringListModel>
#include <memory>

ReaderCallbacks::ReaderCallbacks(otf2::reader::reader &rdr) :
    rdr_(rdr),
    slots_(std::make_shared<std::vector<Slot>>()),
    communications_(std::make_shared<std::vector<Communication>>()),
    slotsBuilding(),
    program_start_() {

}


std::shared_ptr<std::vector<Slot>> ReaderCallbacks::getSlots() {
    return this->slots_;
}

std::shared_ptr<std::vector<Communication>> ReaderCallbacks::getCommunications() {
    return this->communications_;
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
    auto region = event.region();
    auto location = loc;
    builder.start(start)->location(location)->region(region);

    std::vector<Slot::Builder> *builders;
    auto buildersIt = this->slotsBuilding.find(location.ref());
    if (buildersIt == this->slotsBuilding.end()) {
        builders = new std::vector<Slot::Builder>();
        this->slotsBuilding.insert({location.ref(), builders});
    } else {
        builders = buildersIt->second;
    }

    builders->push_back(builder);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::leave &event) {
    auto builders = this->slotsBuilding.at(location.ref());

    Slot::Builder &builder = builders->back();

    auto end = event.timestamp() - this->program_start_;
    builder.end(end);

    this->slots_->push_back(builder.build());

    builders->pop_back();
}

void ReaderCallbacks::communicationEvent(otf2::definition::location location, uint32_t matching,
                                         otf2::chrono::time_point timestamp,
                                         std::map<uint32_t, std::vector<Communication::Builder> *>& selfPending,
                                         std::map<uint32_t, std::vector<Communication::Builder> *>& matchingPending,
                                         std::function<Communication::Builder *(Communication::Builder &,
                                                                                otf2::definition::location &)> &setLocation,
                                         std::function<Communication::Builder *(Communication::Builder &,
                                                                                otf2::chrono::duration &)> &setTime
) {
    auto self = location.ref().get();
    // Check for a pending matching receive call
    if (matchingPending.contains(matching)) {
        auto builderStack = matchingPending[matching];
        auto builder = builderStack->back();


        auto timepoint = timestamp - this->program_start_;
        setLocation(builder, location);
        setTime(builder, timepoint);

        auto communication = builder.build();

        this->communications_->push_back(communication);

        builderStack->pop_back();
        if (builderStack->empty()) {
            delete builderStack;
            matchingPending.erase(matching);
        }
    } else {
        std::vector<Communication::Builder> *builderStack;
        if (selfPending.contains(self)) {
            builderStack = selfPending[self];
        } else {
            builderStack = new std::vector<Communication::Builder>();
            selfPending[self] = builderStack;
        }

        Communication::Builder builder;

        auto timepoint = timestamp - this->program_start_;
        setLocation(builder, location);
        setTime(builder, timepoint);

        builderStack->push_back(builder);
    }
}

void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::mpi_send &send) {
    std::function<Communication::Builder*(Communication::Builder&, otf2::definition::location&)> l = &Communication::Builder::sender;
    std::function<Communication::Builder*(Communication::Builder&, otf2::chrono::duration &)> t = &Communication::Builder::start;
    this->communicationEvent(loc, send.receiver(), send.timestamp(), pendingSends, pendingReceives, l, t);
}

void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::mpi_receive &receive) {
    std::function<Communication::Builder*(Communication::Builder&, otf2::definition::location&)> l = &Communication::Builder::receiver;
    std::function<Communication::Builder*(Communication::Builder&, otf2::chrono::duration &)> t = &Communication::Builder::end;
    this->communicationEvent(loc, receive.sender(), receive.timestamp(), pendingReceives, pendingSends, l, t);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_isend_request &request) {
    std::function<Communication::Builder*(Communication::Builder&, otf2::definition::location&)> l = &Communication::Builder::sender;
    std::function<Communication::Builder*(Communication::Builder&, otf2::chrono::duration &)> t = &Communication::Builder::start;
    this->communicationEvent(location, request.receiver(), request.timestamp(), pendingSends, pendingReceives, l, t);


}

void
ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_isend_complete &complete) {
    callback::event(location, complete);
}

void
ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_ireceive_complete &complete) {
    callback::event(location, complete);
}

void
ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_ireceive_request &request) {
    callback::event(location, request);
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
    callback::event(location, begin);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_collective_end &anEnd) {
    callback::event(location, anEnd);
}


void ReaderCallbacks::events_done(const otf2::reader::reader &) {
    std::sort(this->slots_->begin(), this->slots_->end(), [](Slot &rhs, Slot &lhs) {
        return rhs.start < lhs.start;
    });
    std::sort(this->communications_->begin(), this->communications_->end(), [](Communication &rhs, Communication &lhs) {
        return rhs.start < lhs.start;
    });

    for (const auto &item: this->slotsBuilding) {
        delete item.second;
    }
    for (const auto &item: this->pendingSends) {
        delete item.second;
    }
    for (const auto &item: this->pendingReceives) {
        delete item.second;
    }
    std::destroy(this->slotsBuilding.begin(), this->slotsBuilding.end());
    std::destroy(this->pendingSends.begin(), this->pendingSends.end());
    std::destroy(this->pendingReceives.begin(), this->pendingReceives.end());
}
