#include "subtrace.hpp"


SubTrace::SubTrace(const Range<Slot> &slots, const Range<BlockingP2PCommunication> &blockingP2PCommunications,
                   const Range<NonBlockingP2PCommunication> &nonBlockingP2PCommunications,
                   const Range<CollectiveCommunication> &collectiveCommunications,
                   const otf2::chrono::duration &runtime, const otf2::chrono::duration &startTime) :
    slots_(slots),
    blockingP2PCommunications_(blockingP2PCommunications),
    nonBlockingP2PCommunications_(nonBlockingP2PCommunications),
    collectiveCommunications_(collectiveCommunications),
    runtime_(runtime),
    startTime_(startTime) {}

SubTrace::SubTrace()
    : slots_(),
      blockingP2PCommunications_(),
      nonBlockingP2PCommunications_(),
      collectiveCommunications_(),
      runtime_(),
      startTime_() {};

Range<Slot> SubTrace::getSlots() const {
    return slots_;
}

otf2::chrono::duration SubTrace::getRuntime() const {
    return runtime_;
}

Range<BlockingP2PCommunication> SubTrace::getBlockingP2PCommunications() const {
    return blockingP2PCommunications_;
}

Range<NonBlockingP2PCommunication> SubTrace::getNonBlockingP2PCommunications() const {
    return nonBlockingP2PCommunications_;
}

Range<CollectiveCommunication> SubTrace::getCollectiveCommunications() const {
    return collectiveCommunications_;
}

otf2::chrono::duration SubTrace::getStartTime() const {
    return startTime_;
}


template <typename T>
using TimeAccessor = std::function<otf2::chrono::duration (T const &)>;

namespace accessors {
    const TimeAccessor<Slot> slotStart = &Slot::start;
    const TimeAccessor<Slot> slotEnd = &Slot::end;

    const TimeAccessor<BlockingP2PCommunication> blockingComStart = &BlockingP2PCommunication::sendTime;
    const TimeAccessor<BlockingP2PCommunication> blockingComEnd = &BlockingP2PCommunication::receiveTime;

    const TimeAccessor<NonBlockingP2PCommunication> nonBlockingComStart = &NonBlockingP2PCommunication::sendStartTime;
    const TimeAccessor<NonBlockingP2PCommunication> nonBlockingComEnd = &NonBlockingP2PCommunication::receiveEndTime;

    const TimeAccessor<CollectiveCommunication> collectiveComStart = &CollectiveCommunication::startTime;
    const TimeAccessor<CollectiveCommunication> collectiveComEnd = &CollectiveCommunication::endTime;
};

template <typename T>
static Range<T> subRange(Range<T> r, otf2::chrono::duration from, otf2::chrono::duration to, TimeAccessor<T> getStart, TimeAccessor<T> getEnd) {
    auto start = std::upper_bound(r.begin(), r.end(), from, [getStart](otf2::chrono::duration val, T x) {return val < getStart(x);});
    auto end = std::upper_bound(r.begin(), r.end(), to, [getEnd](otf2::chrono::duration val, T x) {return val < getEnd(x);});

    // No start element found. Start range with first element.
    if(start == r.end()) {
        start = r.begin();
    }

    Range<T> newRange(start, end);

    return newRange;
}

std::shared_ptr<Trace> SubTrace::subtrace(otf2::chrono::duration from, otf2::chrono::duration to) const {
    auto newSlots = subRange(getSlots(), from, to, accessors::slotStart, accessors::slotEnd);
    auto newBlockingComms = subRange(getBlockingP2PCommunications(), from, to, accessors::blockingComStart, accessors::blockingComEnd);
    auto newNonBlockingComms = subRange(getNonBlockingP2PCommunications(), from, to, accessors::nonBlockingComStart, accessors::nonBlockingComEnd);
    auto newCollectiveComms = subRange(getCollectiveCommunications(), from, to, accessors::collectiveComStart, accessors::collectiveComEnd);

    std::shared_ptr<SubTrace> trace(new SubTrace(newSlots, newBlockingComms, newNonBlockingComms, newCollectiveComms, to - from, from));

    return trace;
}
