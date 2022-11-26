#include "filetrace.hpp"

FileTrace::FileTrace(std::vector<Slot> &slotss,
                     std::vector<Communication> &communications,
                     std::vector<CollectiveCommunicationEvent> &collectiveCommunications_,
                     otf2::chrono::duration runtime) :
    slots_(slotss),
    communications_(communications),
    collectiveCommunications_(collectiveCommunications_){
    runtime_ = runtime;
    startTime_ = otf2::chrono::duration(0);
}

Range<Slot> FileTrace::getSlots() const {
    return Range(slots_);
}

Range<Communication> FileTrace::getCommunications() const {
    return Range(communications_);
}

Range<CollectiveCommunicationEvent> FileTrace::getCollectiveCommunications() const {
    return Range(collectiveCommunications_);
}
