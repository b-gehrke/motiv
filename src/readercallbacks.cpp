#include "readercallbacks.hpp"
#include "src/models/communication.hpp"
#include "src/models/slot.hpp"
#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include <QStringListModel>
#include <memory>
#include <utility>

ReaderCallbacks::ReaderCallbacks(otf2::reader::reader &rdr) :
    rdr_(rdr),
    slots_(std::make_shared<std::vector<Slot>>()),
    blockingComm_(std::make_shared<std::vector<BlockingP2PCommunication>>()),
    nonBlockingComm_(std::make_shared<std::vector<NonBlockingP2PCommunication>>()),
    collectiveComm_(std::make_shared<std::vector<CollectiveCommunication>>()),
    slotsBuilding(),
    program_start_() {

}


std::shared_ptr<std::vector<Slot>> ReaderCallbacks::getSlots() {
    return this->slots_;
}

std::shared_ptr<std::vector<BlockingP2PCommunication>> ReaderCallbacks::getBlockingComm() {
    return this->blockingComm_;
}

std::shared_ptr<std::vector<NonBlockingP2PCommunication>> ReaderCallbacks::getNonBlockingComm() {
    return this->nonBlockingComm_;
}

std::shared_ptr<std::vector<CollectiveCommunication>> ReaderCallbacks::getCollectiveComm() {
    return this->collectiveComm_;
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

template<typename T>
void ReaderCallbacks::communicationEvent(otf2::definition::location location, uint32_t matching,
                                         otf2::chrono::time_point timestamp,
                                         std::map<uint32_t, std::vector<typename T::Builder> *> &selfPending,
                                         std::map<uint32_t, std::vector<typename T::Builder> *> &matchingPending,
                                         BuilderSetLocation<T> &setLocation,
                                         BuilderSetTime<T> &setTime
) {
    BuilderSetter<T> empty;
    communicationEvent<T>(
        std::move(location), matching, timestamp, selfPending, matchingPending, setLocation, setTime, empty);
}

template<typename T>
void ReaderCallbacks::communicationEvent(otf2::definition::location location, uint32_t matching,
                                         otf2::chrono::time_point timestamp,
                                         std::map<uint32_t, std::vector<typename T::Builder> *> &selfPending,
                                         std::map<uint32_t, std::vector<typename T::Builder> *> &matchingPending,
                                         BuilderSetLocation<T> &setLocation,
                                         BuilderSetTime<T> &setTime,
                                         BuilderSetter<T> &additionalBuilderSetter
) {
    using Builder = typename T::Builder;
    auto self = location.ref().get();
    // Check for a pending matching receive call
    if (matchingPending.contains(matching)) {
        auto builderStack = matchingPending[matching];
        auto builder = builderStack->back();


        auto timepoint = timestamp - this->program_start_;
        setLocation(builder, location);
        setTime(builder, timepoint);
        if (additionalBuilderSetter) {
            additionalBuilderSetter(builder);
        }

        auto communication = builder.build();

        this->blockingComm_->push_back(communication);

        builderStack->pop_back();
        if (builderStack->empty()) {
            delete builderStack;
            matchingPending.erase(matching);
        }
    } else {
        std::vector<Builder> *builderStack;
        if (selfPending.contains(self)) {
            builderStack = selfPending[self];
        } else {
            builderStack = new std::vector<Builder>();
            selfPending[self] = builderStack;
        }

        Builder builder;

        auto timepoint = timestamp - this->program_start_;
        setLocation(builder, location);
        setTime(builder, timepoint);

        if (additionalBuilderSetter) {
            additionalBuilderSetter(builder);
        }

        builderStack->push_back(builder);
    }
}

void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::mpi_send &send) {
    BuilderSetLocation<BlockingP2PCommunication> setLocation = &BlockingP2PCommunication::Builder::sender;
    BuilderSetTime<BlockingP2PCommunication> setTime = &BlockingP2PCommunication::Builder::sendTime;

    BuilderSetter<BlockingP2PCommunication> setter = [send](BlockingP2PCommunication::Builder &builder) {
        auto len = send.msg_length();
        auto tag = send.msg_tag();
        auto comm = send.comm();
        builder.msgLength(len);
        builder.msgTag(tag);
        builder.communicator(comm);
    };

    this->communicationEvent<BlockingP2PCommunication>(loc, send.receiver(), send.timestamp(), pendingSends,
                                                       pendingReceives, setLocation, setTime, setter);
}

void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::mpi_receive &receive) {
    BuilderSetLocation<BlockingP2PCommunication> setLocation = &BlockingP2PCommunication::Builder::receiver;
    BuilderSetTime<BlockingP2PCommunication> setTime = &BlockingP2PCommunication::Builder::receiveTime;
    this->communicationEvent<BlockingP2PCommunication>(loc, receive.sender(), receive.timestamp(), pendingReceives,
                                                       pendingSends, setLocation, setTime);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::mpi_isend_request &request) {


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
    std::sort(this->blockingComm_->begin(), this->blockingComm_->end(),
              [](BlockingP2PCommunication &rhs, BlockingP2PCommunication &lhs) {
                  return rhs.sendTime < lhs.sendTime;
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
