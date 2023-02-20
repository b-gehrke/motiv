#include "UITrace.hpp"

UITrace::UITrace(std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> slotsVec,
                 const Range<Communication *> &communications,
                 const Range<CollectiveCommunicationEvent *> &collectiveCommunications,
                 const otf2::chrono::duration &runtime, const otf2::chrono::duration &startTime,
                 const otf2::chrono::duration &timePerPx) :
    SubTrace(),
    timePerPx_(timePerPx),
    slotsVec_(std::move(slotsVec)) {
    communications_ = communications;
    collectiveCommunications_ = collectiveCommunications;
    runtime_ = runtime;
    startTime_ = startTime;

    for (auto &item: slotsVec_) {
        slots_.insert({item.first, Range(item.second)});
    }
}

UITrace *UITrace::forResolution(Trace *trace, otf2::chrono::duration timePerPixel) {
    auto minDuration = timePerPixel * MIN_SLOT_SIZE_PX;
    std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> groupedSlots;
    std::map<otf2::definition::location_group *, Range<Slot *>, LocationGroupCmp> groupedSlotsRange;

    for (const auto &item: trace->getSlots()) {
        auto locationGroup = item.first;
        auto slots = item.second;
        std::vector<Slot *> newSlots;

        Slot *intervalStarter = nullptr;
        std::map<SlotKind, std::vector<Slot *>> *stats = nullptr;


        for (const auto &slot: slots) {
            if (intervalStarter != nullptr && (slot->startTime > intervalStarter->startTime + minDuration)) {
                Slot *newSlot;
                // Order of importance if overlapping, the slot with the most important kind is shown.
                // 1. MPI events, 2. OpenMP events 3. all other events
                if (stats->contains(MPI)) {
                    auto mpiStats = stats->at(MPI);
                    newSlot = aggregateSlots(minDuration, intervalStarter, mpiStats);
                } else if (stats->contains(OpenMP)) {
                    auto openMpStats = stats->at(OpenMP);
                    newSlot = aggregateSlots(minDuration, intervalStarter, openMpStats);
                } else {
                    auto plainStats = stats->at(Plain);
                    newSlot = aggregateSlots(minDuration, intervalStarter, plainStats);
                }

                delete stats;
                stats = nullptr;
                intervalStarter = nullptr;

                newSlots.push_back(newSlot);
            }

            if (slot->getDuration() < minDuration) {
                if (intervalStarter == nullptr) {
                    intervalStarter = slot;
                    stats = new std::map<SlotKind, std::vector<Slot *>>();
                }

                if (!stats->contains(slot->getKind())) {
                    stats->insert({slot->getKind(), std::vector<Slot *>()});
                }

                stats->at(slot->getKind()).push_back(slot);
            } else {
                newSlots.push_back(slot);
            }
        }


        groupedSlots.insert({locationGroup, newSlots});
    }

    minDuration = timePerPixel * MIN_COLLECTIVE_EVENT_SIZE_PX;

    std::vector<CollectiveCommunicationEvent *> newCollectiveCommunications;
    CollectiveCommunicationEvent *intervalStarter = nullptr;
    std::vector<CollectiveCommunicationEvent *> interval;
    for (const auto &collectiveCommunication: trace->getCollectiveCommunications()) {


        if (intervalStarter != nullptr &&
            (collectiveCommunication->getStartTime() > intervalStarter->getStartTime() + minDuration)) {
            CollectiveCommunicationEvent *newEvent = aggregateCollectiveCommunications(minDuration, intervalStarter, interval);
            intervalStarter = nullptr;

            newCollectiveCommunications.push_back(newEvent);

            interval.clear();
        }



        if (collectiveCommunication->getDuration() < minDuration) {
            if (intervalStarter == nullptr) {
                intervalStarter = collectiveCommunication;
            }

            interval.push_back(collectiveCommunication);
        } else {
            newCollectiveCommunications.push_back(collectiveCommunication);
        }

    }

    return new UITrace(groupedSlots, trace->getCommunications(), Range(newCollectiveCommunications),
                       trace->getRuntime(), trace->getStartTime(), timePerPixel);
}

Trace *UITrace::subtrace(otf2::chrono::duration from, otf2::chrono::duration to) {
    return forResolution(SubTrace::subtrace(from, to), timePerPx_);
}


template<class T>
requires std::is_base_of_v<TimedElement, T>
static T *longest(std::vector<T *> ls) {
    return *std::max_element(ls.begin(), ls.end(), [](T *lhs, T *rhs) {
        return lhs->getDuration() > rhs->getDuration();
    });
}

template<class T>
requires std::is_base_of_v<TimedElement, T>
static T *last(std::vector<T *> ls) {
    return *std::max_element(ls.begin(), ls.end(), [](T *lhs, T *rhs) {
        return lhs->getEndTime() < rhs->getEndTime();
    });
}


Slot *UITrace::aggregateSlots(otf2::chrono::duration minDuration,
                              const Slot *intervalStarter,
                              std::vector<Slot *> &stats) {
    auto longestSlot = longest(stats);
    auto intervalEnder = last(stats);

    return new Slot(intervalStarter->startTime, intervalEnder->endTime, longestSlot->location, longestSlot->region);
}

UITrace *UITrace::forResolution(Trace *trace, int width) {
    return forResolution(trace, trace->getRuntime() / width);
}

CollectiveCommunicationEvent *UITrace::aggregateCollectiveCommunications(otf2::chrono::duration minDuration,
                                                                         const CollectiveCommunicationEvent *intervalStarter,
                                                                         std::vector<CollectiveCommunicationEvent *> &stats) {
    auto longestEvent = longest(stats);
    auto intervalEnder = last(stats);

    auto singleMember = new CollectiveCommunicationEvent::Member(intervalStarter->getStartTime(),
                                                                    intervalEnder->getEndTime(),
                                                                    longestEvent->getLocation());

    std::vector<CollectiveCommunicationEvent::Member*> singletonMembers;
    singletonMembers.push_back(singleMember);

    return new CollectiveCommunicationEvent(
        singletonMembers, longestEvent->getLocation(), longestEvent->getCommunicator(),
        longestEvent->getOperation(), longestEvent->getRoot()
    );
}
