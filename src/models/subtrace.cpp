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
    return val < x.start;
}

template<typename T>
static bool compareEnd(otf2::chrono::duration val, T x) {
    return val < x.end;
}


std::shared_ptr<Trace> SubTrace::subtrace(otf2::chrono::duration from, otf2::chrono::duration to) const {
    auto slots = getSlots();
    auto communications = getCommunications();

    auto newSlotsStart = std::upper_bound(slots.begin(), slots.end(), from, &compareStart<Slot>);
    auto newSlotsEnd = std::upper_bound(slots.begin(), slots.end(), to, &compareEnd<Slot>);
    auto newComsStart = std::upper_bound(communications.begin(), communications.end(), from, &compareStart<Communication>);
    auto newComsEnd = std::upper_bound(communications.begin(), communications.end(), to, &compareEnd<Communication>);

    // No start element found. Start subtrace with first element
    if(newSlotsStart == slots.end()){
        newSlotsStart = slots.begin();
    }

    if(newComsStart == communications.end()) {
        newComsStart = communications.begin();
    }

    Range<Slot> newSlots(newSlotsStart, newSlotsEnd);
    Range<Communication> newComs(newComsStart, newComsEnd);

    auto slotStartTime = !newSlots.empty() ? newSlotsStart->start : otf2::chrono::duration::max();
    auto slotEndTime = !newSlots.empty() ? (newSlotsEnd - 1)->end : otf2::chrono::duration::min();

    auto comStartTime = !newComs.empty() ? newComsStart->start : otf2::chrono::duration::max();
    auto comEndTime = !newComs.empty() ? (newComsEnd - 1)->end : otf2::chrono::duration::min();

    auto startTime = std::min(slotStartTime, comStartTime);
    auto endTime = std::max(slotEndTime, comEndTime);

    auto subRuntime = endTime - startTime;

    std::shared_ptr<SubTrace> trace(new SubTrace(newSlots, newComs, subRuntime));

    return trace;

}

SubTrace::SubTrace() : slots_(), communications_(), runtime_() {

}
