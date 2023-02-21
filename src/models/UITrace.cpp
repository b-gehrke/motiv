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
        std::map<SlotKind, std::vector<Slot *>> stats;

        for (const auto &slot: slots) {
            if (intervalStarter != nullptr && (slot->startTime > intervalStarter->startTime + minDuration)) {
                Slot *newSlot;
                // Order of importance if overlapping, the slot with the most important kind is shown.
                // 1. MPI events, 2. OpenMP events 3. all other events
                if (stats.contains(MPI)) {
                    auto mpiStats = stats.at(MPI);
                    newSlot = aggregateSlots(minDuration, intervalStarter, mpiStats);
                } else if (stats.contains(OpenMP)) {
                    auto openMpStats = stats.at(OpenMP);
                    newSlot = aggregateSlots(minDuration, intervalStarter, openMpStats);
                } else {
                    auto plainStats = stats.at(Plain);
                    newSlot = aggregateSlots(minDuration, intervalStarter, plainStats);
                }

                stats.clear();
                intervalStarter = nullptr;

                newSlots.push_back(newSlot);
            }

            if (slot->getDuration() < minDuration) {
                if (intervalStarter == nullptr) {
                    intervalStarter = slot;
                }

                if (!stats.contains(slot->getKind())) {
                    stats.insert({slot->getKind(), std::vector<Slot *>()});
                }

                stats.at(slot->getKind()).push_back(slot);
            } else {
                newSlots.push_back(slot);
            }
        }
        if(intervalStarter){
            Slot *newSlot;
            // Order of importance if overlapping, the slot with the most important kind is shown.
            // 1. MPI events, 2. OpenMP events 3. all other events
            if (stats.contains(MPI)) {
                auto mpiStats = stats.at(MPI);
                newSlot = aggregateSlots(minDuration, intervalStarter, mpiStats);
            } else if (stats.contains(OpenMP)) {
                auto openMpStats = stats.at(OpenMP);
                newSlot = aggregateSlots(minDuration, intervalStarter, openMpStats);
            } else {
                auto plainStats = stats.at(Plain);
                newSlot = aggregateSlots(minDuration, intervalStarter, plainStats);
            }

            newSlots.push_back(newSlot);
        }


        groupedSlots.insert({locationGroup, newSlots});
    }


    minDuration = timePerPixel * MIN_COMMUNICATION_SIZE_PX;
    auto traceCommunications = trace->getCommunications();
    std::vector<Communication*> communications(traceCommunications.begin(), traceCommunications.end());
    std::map<otf2::reference<otf2::definition::location_group>, Range<Communication*>> communicationsByRank;
    
    // Sort first by location group aka MPI Rank, second by start time
    std::sort(communications.begin(), communications.end(), [](const Communication* l, const Communication* r) {
        auto rankL = l->getStartEvent()->getLocation()->location_group().ref();
        auto rankR = r->getStartEvent()->getLocation()->location_group().ref();

        if(rankL == rankR) {
            return l->getStartTime() < r->getStartTime();
        }

        return rankL < rankR;
    });

    if(!communications.empty()) {
        // group by location group aka MPI Rank
        auto start = communications.begin();
        auto it = communications.begin() + 1;
        while (it != communications.end()) {
            auto rank = (*it)->getStartEvent()->getLocation()->location_group().ref();
            auto startRank = (*start)->getStartEvent()->getLocation()->location_group().ref();
            if (rank != startRank) {
                communicationsByRank[startRank] = Range<Communication*>(start, it);
                start = it;
            }

            it++;
        }
        auto startRank = (*start)->getStartEvent()->getLocation()->location_group().ref();
        communicationsByRank[startRank] = Range<Communication*>(start, it);
    }

    std::vector<Communication*> newCommunications;
    for (const auto &item: communicationsByRank) {
        auto rank = item.first;
        auto comms = item.second;

        Communication *intervalStarter = nullptr;


        for (const auto &comm: comms) {
            if (intervalStarter != nullptr && (comm->getStartTime() > intervalStarter->getStartTime() + minDuration)) {
                newCommunications.push_back(intervalStarter);

                intervalStarter = nullptr;
            }

            if (comm->getDuration() < minDuration) {
                if (intervalStarter == nullptr) {
                    intervalStarter = comm;
                }
            } else {
                newCommunications.push_back(comm);
            }
        }
        if(intervalStarter) {
            newCommunications.push_back(intervalStarter);
        }
    }


    minDuration = timePerPixel * MIN_COLLECTIVE_EVENT_SIZE_PX;

    std::vector<CollectiveCommunicationEvent *> newCollectiveCommunications;
    CollectiveCommunicationEvent *collectiveIntervalStarter = nullptr;
    std::vector<CollectiveCommunicationEvent *> collectiveInterval;
    for (const auto &collectiveCommunication: trace->getCollectiveCommunications()) {


        if (collectiveIntervalStarter != nullptr &&
            (collectiveCommunication->getStartTime() > collectiveIntervalStarter->getStartTime() + minDuration)) {
            CollectiveCommunicationEvent *newEvent = aggregateCollectiveCommunications(minDuration, collectiveIntervalStarter, collectiveInterval);

            collectiveIntervalStarter = nullptr;
            collectiveInterval.clear();

            newCollectiveCommunications.push_back(newEvent);
        }



        if (collectiveCommunication->getDuration() < minDuration) {
            if (collectiveIntervalStarter == nullptr) {
                collectiveIntervalStarter = collectiveCommunication;
            }

            collectiveInterval.push_back(collectiveCommunication);
        } else {
            newCollectiveCommunications.push_back(collectiveCommunication);
        }
    }
    if(collectiveIntervalStarter) {
        CollectiveCommunicationEvent *newEvent = aggregateCollectiveCommunications(minDuration, collectiveIntervalStarter, collectiveInterval);
        newCollectiveCommunications.push_back(newEvent);
    }

    return new UITrace(groupedSlots, Range(newCommunications), Range(newCollectiveCommunications),
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
