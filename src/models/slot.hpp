#ifndef MOTIV_SLOT_HPP
#define MOTIV_SLOT_HPP

#include <otf2xx/otf2.hpp>
#include "builder.hpp"


class Slot {
public:
    Slot(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
         otf2::definition::location location, otf2::definition::region region);

    otf2::chrono::duration start;
    otf2::chrono::duration end;
    otf2::definition::location location;
    otf2::definition::region region;

    BUILDER(Slot,
            BUILDER_FIELD(otf2::chrono::duration, start)
            BUILDER_FIELD(otf2::chrono::duration, end)
            BUILDER_FIELD(otf2::definition::location, location)
            BUILDER_FIELD(otf2::definition::region, region),
            start, end, location, region)
};

#endif //MOTIV_SLOT_HPP
