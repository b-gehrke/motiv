#include "subtrace.hpp"

#include <utility>


SubTrace::SubTrace(std::map<otf2::definition::location_group, Range<Slot>, LocationGroupCmp> slots,
                   const Range<Communication> &communications,
                   const Range<CollectiveCommunicationEvent> &collectiveCommunications,
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

std::map<otf2::definition::location_group, Range<Slot>, LocationGroupCmp> SubTrace::getSlots() const {
    return slots_;
}

otf2::chrono::duration SubTrace::getRuntime() const {
    return runtime_;
}

Range<Communication> SubTrace::getCommunications() const {
    return communications_;
}

Range<CollectiveCommunicationEvent> SubTrace::getCollectiveCommunications() const {
    return collectiveCommunications_;
}

otf2::chrono::duration SubTrace::getStartTime() const {
    return startTime_;
}


template<typename T>
using TimeAccessor = std::function<otf2::chrono::duration(T const &)>;

namespace accessors {
    const TimeAccessor<Slot> slotStart = &Slot::start;
    const TimeAccessor<Slot> slotEnd = &Slot::end;

    const TimeAccessor<CommunicationEvent> communicationEventStart = &CommunicationEvent::getStart;
    const TimeAccessor<CommunicationEvent> communicationEventEnd = &CommunicationEvent::getEnd;


    const TimeAccessor<CollectiveCommunicationEvent> colelctiveCommunicationEventStart = &CollectiveCommunicationEvent::getStart;
    const TimeAccessor<CollectiveCommunicationEvent> colelctiveCommunicationEventEnd = &CollectiveCommunicationEvent::getEnd;

    const TimeAccessor<Communication> communicationStart = [](
        const Communication &e) { return e.getStart()->getStart(); };
    const TimeAccessor<Communication> communicationEnd = [](const Communication &e) { return e.getEnd()->getEnd(); };
};

template<typename T>
static Range<T> subRange(Range<T> r, otf2::chrono::duration from, otf2::chrono::duration to, TimeAccessor<T> getStart,
                         TimeAccessor<T> getEnd) {
    auto start = std::upper_bound(r.begin(), r.end(), from,
                                  [getStart](otf2::chrono::duration val, T x) { return val < getStart(x); });
    auto end = std::upper_bound(r.begin(), r.end(), to,
                                [getEnd](otf2::chrono::duration val, T x) { return val < getEnd(x); });

    // No start element found. Start range with first element.
    if (start == r.end()) {
        start = r.begin();
    }

    Range<T> newRange(start, end);

    return newRange;
}


std::shared_ptr<Trace> SubTrace::subtrace(otf2::chrono::duration from, otf2::chrono::duration to) const {
    std::map<otf2::definition::location_group, Range<Slot>, LocationGroupCmp> newSlots;
    for (const auto &item: getSlots()) {
        Range<Slot> slots = subRange(item.second, from, to, accessors::slotStart, accessors::slotEnd);
        newSlots.insert({item.first, slots});
    }
    auto newCommunications = subRange(getCommunications(), from, to, accessors::communicationStart,
                                      accessors::communicationEnd);
    auto newCollectiveCommunications = subRange<CollectiveCommunicationEvent>(getCollectiveCommunications(),
                                                                              from,
                                                                              to,
                                                                              accessors::communicationEventStart,
                                                                              accessors::communicationEventEnd);

    std::shared_ptr<SubTrace> trace(new SubTrace(newSlots, newCommunications, newCollectiveCommunications, to - from, from));

    return trace;
}

