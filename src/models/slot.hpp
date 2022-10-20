//
// Created by bjoern on 20.10.22.
//

#ifndef MOTIV_SLOT_HPP
#define MOTIV_SLOT_HPP

#include <otf2xx/otf2.hpp>

class Slot {
public:
    Slot(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
         otf2::definition::location location, otf2::definition::region region);
    Slot(const otf2::chrono::duration &start,
         otf2::definition::location location, otf2::definition::region region);

    otf2::chrono::duration start;
    otf2::chrono::duration end{};
    otf2::definition::location location;
    otf2::definition::region region;


};
#endif //MOTIV_SLOT_HPP
