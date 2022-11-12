#include "subtrace.hpp"


SubTrace::SubTrace(const Range<Slot> &slots, const Range<Communication> &communications,
                   const otf2::chrono::duration &runtime, const otf2::chrono::duration &startTime) :
    slots_(slots),
    communications_(communications),
    runtime_(runtime),
    startTime_(startTime) {}

SubTrace::SubTrace()
    : slots_(),
      communications_(),
      runtime_(),
      startTime_() {};

Range<Slot> SubTrace::getSlots() const {
    return slots_;
}

otf2::chrono::duration SubTrace::getRuntime() const {
    return runtime_;
}

Range<Communication> SubTrace::getCommunications() const {
    return communications_;
}

otf2::chrono::duration SubTrace::getStartTime() const {
    return startTime_;
}


template<typename T>
using TimeAccessor = std::function<otf2::chrono::duration(T const &)>;

namespace accessors {
    const TimeAccessor<Slot> slotStart = &Slot::start;
    const TimeAccessor<Slot> slotEnd = &Slot::end;

    const TimeAccessor<Communication> communicationStart = [](const Communication& e) { return e.getStart()->getStart(); };
    const TimeAccessor<Communication> communicationEnd = [](const Communication& e) { return e.getEnd()->getEnd(); };
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
    auto newSlots = subRange(getSlots(), from, to, accessors::slotStart, accessors::slotEnd);
    auto newCommunications = subRange(getCommunications(), from, to, accessors::communicationStart,
                                      accessors::communicationEnd);

    std::shared_ptr<SubTrace> trace(new SubTrace(newSlots, newCommunications, to - from, from));

    return trace;
}
