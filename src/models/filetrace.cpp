#include "filetrace.hpp"

FileTrace::FileTrace(std::vector<Slot> &slotss,
                     std::vector<Communication> &communications,
                     std::vector<CollectiveCommunicationEvent> &collectiveCommunications_,
                     otf2::chrono::duration runtime) :
    slotsVec_(std::map<otf2::definition::location_group, std::vector<Slot>, LocationGroupCmp>()),
    communications_(communications),
    collectiveCommunications_(collectiveCommunications_){
    runtime_ = runtime;
    startTime_ = otf2::chrono::duration(0);

    // Sort first by location group aka MPI Rank, second by start time
    std::sort(slotss.begin(), slotss.end(), [](const Slot& l, const Slot& r) {
        auto groupL = l.location.location_group();
        auto groupR = r.location.location_group();

        if(groupL.ref() == groupR.ref()) {
            return l.start < r.start;
        }

        return groupL.ref() < groupR.ref();
    });

    if(slotss.empty()) {
        return;
    }

    // group by location group aka MPI Rank
    auto start = slotss.begin();
    auto it = slotss.begin() + 1;
    while(it != slotss.end()) {
        if(it->location.location_group() != start->location.location_group()) {
            slots_[start->location.location_group()] = Range<Slot>(start, it);
            start = it;
        }

        it++;
    }
    slots_[start->location.location_group()] = Range<Slot>(start, it);
}

std::map<otf2::definition::location_group, Range<Slot>, LocationGroupCmp> FileTrace::getSlots() const {
    return slots_;
}

Range<Communication> FileTrace::getCommunications() const {
    return Range(communications_);
}

Range<CollectiveCommunicationEvent> FileTrace::getCollectiveCommunications() const {
    return Range(collectiveCommunications_);
}
