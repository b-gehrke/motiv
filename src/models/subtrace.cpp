#include "subtrace.hpp"

SubTrace::SubTrace(const Range<Slot> &slots, const Range<Communication> &communications,
                   otf2::chrono::duration runtime) :
    slots_(slots),
    communications_(communications),
    runtime_(runtime) {}

Range<Slot> SubTrace::getSlots() const {
    return slots_;
}

Range<Communication> SubTrace::getCommunications() const {
    return communications_;
}

otf2::chrono::duration SubTrace::getRuntime() const {
    return runtime_;
}

template<typename T>
static bool compareStart(otf2::chrono::duration val, T x) {
    return x.start < val;
}

template<typename T>
static bool compareEnd(T x, otf2::chrono::duration val) {
    return x.end > val;
}


std::shared_ptr<Trace> SubTrace::subtrace(otf2::chrono::duration from, otf2::chrono::duration to) const {
    auto slots = getSlots();
    auto communications = getCommunications();

    otf2::chrono::duration slotStartTime, slotEndTime, comStartTime, comEndTime;


//    if (!slots.empty()) {
    auto newSlotsStart = std::upper_bound(slots.begin(), slots.end(), from, &compareStart<Slot>);
    auto newSlotsEnd = std::lower_bound(slots.begin(), slots.end(), to, &compareEnd<Slot>);

    Range<Slot> newSlots(newSlotsStart, newSlotsEnd);

    slotStartTime = !newSlots.empty() ? newSlotsStart->start : otf2::chrono::duration::max();
    slotEndTime = !newSlots.empty() ? (newSlotsEnd - 1)->end : otf2::chrono::duration::min();
//    }

    auto newComsStart = std::upper_bound(communications.begin(), communications.end(), from, &compareStart<Communication>);
    auto newComsEnd = std::lower_bound(communications.begin(), communications.end(), to, &compareEnd<Communication>);

    Range<Communication> newComs(newComsStart, newComsEnd);

    comStartTime = !newComs.empty() ? newComsStart->start : otf2::chrono::duration::max();
    comEndTime = !newComs.empty() ? (newComsEnd - 1)->end : otf2::chrono::duration::min();
//    }

    auto startTime = std::min(slotStartTime, comStartTime);
    auto endTime = std::max(slotEndTime, comEndTime);

    auto subRuntime = endTime - startTime;

    std::shared_ptr<SubTrace> trace(new SubTrace(newSlots, newComs, subRuntime));

    return trace;

}

SubTrace::SubTrace() : slots_(), communications_(), runtime_() {

}
