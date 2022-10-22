#include "filetrace.hpp"

FileTrace::FileTrace(std::vector<Slot> &slotss, std::vector<Communication> &communications,
                     otf2::chrono::duration runtime) :
    slotsVec_(slotss), communicationsVec_(communications) {runtime_ = runtime;}

Range<Slot> FileTrace::getSlots() const {
    return Range(slotsVec_);
}

Range<Communication> FileTrace::getCommunications() const {
    return Range(communicationsVec_);
}

