/*
 * Marvelous OTF2 Traces Interactive Visualizer (MOTIV)
 * Copyright (C) 2023 Florian Gallrein, Björn Gehrke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "UITrace.hpp"
#include "src/utils.hpp"

#include <QDebug>

UITrace::UITrace(std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> slotsVec,
                 const Range<Communication *> &communications,
                 const Range<CollectiveCommunicationEvent *> &collectiveCommunications,
                 const otf2::chrono::duration &runtime, const otf2::chrono::duration &startTime,
                 const otf2::chrono::duration &timePerPx) :
    SubTrace(),
    timePerPx_(timePerPx) {
    communications_ = communications;
    collectiveCommunications_ = collectiveCommunications;
    runtime_ = runtime;
    startTime_ = startTime;

    for (auto &item: slotsVec) {
        slots_.insert({item.first, Range(item.second)});
    }
}
UITrace *UITrace::forResolution(Trace *trace, int width) {
    return forResolution(trace, trace->getRuntime() / width);
}

UITrace *UITrace::forResolution(Trace *trace, otf2::chrono::duration timePerPixel) {

    // Optimize slots
    auto minDuration = timePerPixel * MIN_SLOT_SIZE_PX;
    std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> newSlots;
    for (const auto &item: trace->getSlots()) {
        auto locationGroup = item.first;
        auto slots = item.second;
        auto newSlotsForRank = optimize<Slot, SlotKind>(
            minDuration,
            slots,
            &Slot::getKind,
            &UITrace::aggregateSlots);

        newSlots.insert({locationGroup, newSlotsForRank});
    }


    // Optimize communications.
    // Optimization is done per rank of the starting event. This is beneficial if few 1:n communications occur.
    // 1:n communications are only visible with a higher zoom level.
    minDuration = timePerPixel * MIN_COMMUNICATION_SIZE_PX;
    auto communicationsByRank = groupBy<Communication *, otf2::reference<otf2::definition::location_group>>(
        trace->getCommunications(),
        [](const Communication *c) { return c->getStartEvent()->getLocation()->location_group().ref(); },
        [](const Communication *l, const Communication *r) {
            auto rankL = l->getStartEvent()->getLocation()->location_group().ref();
            auto rankR = r->getStartEvent()->getLocation()->location_group().ref();

            if (rankL == rankR) {
                return l->getStartTime() < r->getStartTime();
            }

            return rankL < rankR;
        });

    std::vector<Communication *> newCommunications;
    for (const auto &item: communicationsByRank) {
        auto communications = item.second;
        auto newCommunicationsForRank = optimize<Communication>(
            minDuration,
            communications,
            [](Communication *starter, std::vector<Communication *> &) { return starter; });
        newCommunications.insert(newCommunications.end(), newCommunicationsForRank.begin(),
                                 newCommunicationsForRank.end());
    }


    // Optimize collective communications
    minDuration = timePerPixel * MIN_COLLECTIVE_EVENT_SIZE_PX;
    auto newCollectiveCommunications = optimize<CollectiveCommunicationEvent>(minDuration,
                                                                              trace->getCollectiveCommunications(),
                                                                              &UITrace::aggregateCollectiveCommunications);

    return new UITrace(newSlots, Range(newCommunications), Range(newCollectiveCommunications),
                       trace->getRuntime(), trace->getStartTime(), timePerPixel);
}

template<class T>
requires std::is_base_of_v<TimedElement, T>
std::vector<T *> UITrace::optimize(types::TraceTime minDuration,
                                   Range<T *> elements,
                                   std::function<T *(T *, std::vector<T *> &stats)> aggregate) {
    // This optimization implementation does not group elements in an interval. To not replicate code, it calls the
    // overload that groups and groups all elements into a single group.
    return optimize<T, uint8_t>(
        minDuration,
        elements,
        [](const T *) { return 0; },
        [aggregate](T *starter, std::map<uint8_t, std::vector<T *>> &stats) {
            return aggregate(starter, stats[0]);
        });
}

template<class T, typename K>
requires std::is_base_of_v<TimedElement, T>
std::vector<T *> UITrace::optimize(types::TraceTime minDuration,
                                   Range<T *> &elements,
                                   std::function<K(const T *)> keySelector,
                                   std::function<T *(T *, std::map<K, std::vector<T *>> &stats)> aggregate) {
    std::vector<T *> newElements;
    T *intervalStarter = nullptr;
    std::map<K, std::vector<T *>> stats;

    for (const auto &element: elements) {
        // Check whether the current element is outside the interval (start + minDuration). If so, group interval and continue.
        if (intervalStarter != nullptr && (element->getStartTime() > intervalStarter->getStartTime() + minDuration)) {
            newElements.push_back(aggregate(intervalStarter, stats));

            stats.clear();
            intervalStarter = nullptr;
        }

        // Check if element is too short
        if (element->getDuration() < minDuration) {
            if (intervalStarter == nullptr) {
                intervalStarter = element;
            }

            // Insert element in group
            if (!stats.contains(keySelector(element))) {
                stats.insert({keySelector(element), std::vector<T *>()});
            }

            stats.at(keySelector(element)).push_back(element);
        } else {
            newElements.push_back(element);
        }
    }

    // If the trace ends with a short interval it must be completed.
    if (intervalStarter) {
        newElements.push_back(aggregate(intervalStarter, stats));
    }
    return newElements;
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


Slot *UITrace::aggregateSlots(const Slot *intervalStarter, std::map<SlotKind, std::vector<Slot *>> &stats) {
    std::vector<Slot *>* elements;
    // Order of importance if overlapping, the slot with the most important kind is shown.
    // 1. MPI events, 2. OpenMP events 3. all other events
    if (stats.contains(MPI)) {
        elements = &stats.at(MPI);
    } else if (stats.contains(OpenMP)) {
        elements = &stats.at(OpenMP);
    } else {
        elements = &stats.at(Plain);
    }

    auto longestSlot = longest(*elements);
    auto intervalEnder = last(*elements);

    return new Slot(intervalStarter->startTime, intervalEnder->endTime, longestSlot->location, longestSlot->region);
}

CollectiveCommunicationEvent *UITrace::aggregateCollectiveCommunications(
    const CollectiveCommunicationEvent *intervalStarter,
    std::vector<CollectiveCommunicationEvent *> &stats) {
    auto longestEvent = longest(stats);
    auto intervalEnder = last(stats);

    auto singleMember = new CollectiveCommunicationEvent::Member(intervalStarter->getStartTime(),
                                                                 intervalEnder->getEndTime(),
                                                                 longestEvent->getLocation());

    std::vector<CollectiveCommunicationEvent::Member *> singletonMembers;
    singletonMembers.push_back(singleMember);

    return new CollectiveCommunicationEvent(
        singletonMembers, longestEvent->getLocation(), longestEvent->getCommunicator(),
        longestEvent->getOperation(), longestEvent->getRoot()
    );
}

Trace *UITrace::subtrace(otf2::chrono::duration from, otf2::chrono::duration to) {
    return forResolution(SubTrace::subtrace(from, to), timePerPx_);
}
