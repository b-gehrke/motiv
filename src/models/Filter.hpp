#ifndef MOTIV_FILTER_HPP
#define MOTIV_FILTER_HPP

#define FILTER_DEFAULT ((SlotKind) (SlotKind::MPI | SlotKind::OpenMP | SlotKind::Plain))

#include "slot.hpp"

class Filter {
public: // constructors

public: // methods
    [[nodiscard]] SlotKind getSlotKinds() const;

    void setSlotKinds(SlotKind slotKinds);

private: // fields
    SlotKind slotKinds_ = FILTER_DEFAULT;
};


#endif //MOTIV_FILTER_HPP
