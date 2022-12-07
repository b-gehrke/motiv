#include "filetrace.hpp"

FileTrace::FileTrace(std::vector<Slot> &slotss,
                     std::vector<Communication> &communications,
                     std::vector<CollectiveCommunicationEvent> &collectiveCommunications_,
                     otf2::chrono::duration runtime) :
    slots_(std::map<otf2::definition::location_group, std::vector<Slot>, LocationGroupCmp>()), 
    communications_(communications),
    collectiveCommunications_(collectiveCommunications_){
    runtime_ = runtime;
    startTime_ = otf2::chrono::duration(0);

    for (const auto &slot: slotss) {
        auto group = slot.location.location_group();
        if(!slots_.contains(group)) {
            slots_.insert({group, std::vector<Slot>()});
        }
        slots_[group].push_back(slot);
    }
}

std::map<otf2::definition::location_group, Range<Slot>, LocationGroupCmp> FileTrace::getSlots() const {
    std::map<otf2::definition::location_group, Range<Slot>, LocationGroupCmp> slotss;
    for (const auto &item: slots_){
        std::vector<Slot> v = item.second;
        slotss.insert({item.first, Range<Slot>(v)});
    }

    return slotss;
}

Range<Communication> FileTrace::getCommunications() const {
    return Range(communications_);
}

Range<CollectiveCommunicationEvent> FileTrace::getCollectiveCommunications() const {
    return Range(collectiveCommunications_);
}
