#ifndef MOTIV_SLOT_HPP
#define MOTIV_SLOT_HPP

#include <otf2xx/otf2.hpp>
#include "builder.hpp"

enum SlotKind {
    MPI = 0b0001,
    OpenMP = 0b0010,
    Plain = 0b0100
};

class Slot {
public:
    Slot(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
         otf2::definition::location *location, otf2::definition::region *region);

    /**
     * Start time of the slot relative to the trace start time
     */
    otf2::chrono::duration start;

    /**
     * End time of the slot relative to the trace start time
     */
    otf2::chrono::duration end;

    /**
     * Location of the slot (thread) containing the location group (MPI rank)
     */
    otf2::definition::location *location;

    /**
     * Region the slot occurred in. For example, the source file and line.
     */
    otf2::definition::region *region;

    /**
     * Returns the kind of the slot
     * @return kind of the slot
     */
    [[nodiscard]] SlotKind getKind() const;

    /**
     * Return the duration of the slot
     * @return duration of the slot
     */
    [[nodiscard]] otf2::chrono::duration getDuration() const;

    BUILDER(Slot,
            BUILDER_FIELD(otf2::chrono::duration, start)
                BUILDER_FIELD(otf2::chrono::duration, end)
                BUILDER_FIELD(otf2::definition::location * , location)
                BUILDER_FIELD(otf2::definition::region * , region),
            start, end, location, region)
};

#endif //MOTIV_SLOT_HPP
