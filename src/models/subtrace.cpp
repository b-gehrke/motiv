#include "subtrace.hpp"
#include "range.hpp"

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
    const TimeAccessor<Slot *> slotStart = &Slot::start;
    const TimeAccessor<Slot *> slotEnd = &Slot::end;

    const TimeAccessor<CommunicationEvent *> communicationEventStart = &CommunicationEvent::getStart;
    const TimeAccessor<CommunicationEvent *> communicationEventEnd = &CommunicationEvent::getEnd;


    const TimeAccessor<CollectiveCommunicationEvent *> colelctiveCommunicationEventStart = &CollectiveCommunicationEvent::getStart;
    const TimeAccessor<CollectiveCommunicationEvent *> colelctiveCommunicationEventEnd = &CollectiveCommunicationEvent::getEnd;

    const TimeAccessor<Communication *> communicationStart = [](
        const Communication *e) { return e->getStart()->getStart(); };
    const TimeAccessor<Communication *> communicationEnd = [](const Communication *e) { return e->getEnd()->getEnd(); };
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
        std::sort(slots.begin(), slots.end(), [](const Slot* lhs, const Slot* rhs) {return lhs->start < rhs->start;});
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

