/*
 * Marvellous OTF2 Traces Interactive Visualizer (MOTIV)
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
#include "SubTrace.hpp"
#include "Range.hpp"

#include <utility>


SubTrace::SubTrace(std::map<otf2::definition::location_group *, Range<Slot *>, LocationGroupCmp> &slots,
                   const Range<Communication *> &communications,
                   const Range<CollectiveCommunicationEvent *> &collectiveCommunications,
                   const otf2::chrono::duration &runtime,
                   const otf2::chrono::duration &startTime) :
    slots_(std::move(slots)),
    communications_(communications),
    collectiveCommunications_(collectiveCommunications),
    runtime_(runtime),
    startTime_(startTime) {}

SubTrace::SubTrace()
    : slots_(),
      communications_(),
      collectiveCommunications_(),
      runtime_(),
      startTime_() {};

std::map<otf2::definition::location_group *, Range<Slot *>, LocationGroupCmp> SubTrace::getSlots() const {
    return slots_;
}

otf2::chrono::duration SubTrace::getRuntime() const {
    return runtime_;
}

Range<Communication *> SubTrace::getCommunications() {
    return communications_;
}

Range<CollectiveCommunicationEvent *> SubTrace::getCollectiveCommunications() {
    return collectiveCommunications_;
}

otf2::chrono::duration SubTrace::getStartTime() const {
    return startTime_;
}


template<typename T>
using TimeAccessor = std::function<otf2::chrono::duration(T const &)>;


namespace accessors {
    const TimeAccessor<Slot *> slotStart = &Slot::startTime;
    const TimeAccessor<Slot *> slotEnd = &Slot::endTime;

    const TimeAccessor<CommunicationEvent *> communicationEventStart = &CommunicationEvent::getStartTime;
    const TimeAccessor<CommunicationEvent *> communicationEventEnd = &CommunicationEvent::getEndTime;

    const TimeAccessor<Communication *> communicationStart = [](
        const Communication *e) { return e->getStartEvent()->getStartTime(); };
    const TimeAccessor<Communication *> communicationEnd = [](const Communication *e) { return e->getEndEvent()->getEndTime(); };
};

template<typename T>
static Range<T> subRange(Range<T> r, otf2::chrono::duration from, otf2::chrono::duration to, TimeAccessor<T> getStart,
                         TimeAccessor<T> getEnd) {
    std::vector<T> newVec;
    std::copy_if(r.begin(), r.end(), std::back_inserter(newVec), [from, to, getStart, getEnd](T x) {
        return getStart(x) < to && getEnd(x) > from;
    });

    Range<T> newRange(newVec);

    return newRange;
}


Trace *SubTrace::subtrace(otf2::chrono::duration from, otf2::chrono::duration to) {
    std::map<otf2::definition::location_group *, Range<Slot *>, LocationGroupCmp> newSlots;
    for (const auto &item: getSlots()) {
        Range<Slot *> slots = subRange(item.second, from, to, accessors::slotStart, accessors::slotEnd);
        std::sort(slots.begin(), slots.end(), [](const Slot* lhs, const Slot* rhs) {return lhs->startTime < rhs->startTime;});
        newSlots.insert({item.first, slots});
    }
    auto newCommunications = subRange(getCommunications(), from, to, accessors::communicationStart,
                                      accessors::communicationEnd);
    auto newCollectiveCommunications = subRange<CollectiveCommunicationEvent *>(getCollectiveCommunications(),
                                                                                from,
                                                                                to,
                                                                                accessors::communicationEventStart,
                                                                                accessors::communicationEventEnd);

    auto trace = new SubTrace(newSlots, newCommunications, newCollectiveCommunications, to - from, from);

    return trace;
}

types::TraceTime SubTrace::getEndTime() const {
    return startTime_ + runtime_;
}

types::TraceTime SubTrace::getDuration() const {
    return runtime_;
}

