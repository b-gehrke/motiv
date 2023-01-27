#include "Filter.hpp"

SlotKind Filter::getSlotKinds() const {
    return slotKinds_;
}

void Filter::setSlotKinds(SlotKind slotKinds) {
    slotKinds_ = slotKinds;
}
