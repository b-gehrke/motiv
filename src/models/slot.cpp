#include <utility>

#include "./slot.hpp"

Slot::Slot(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
           otf2::definition::location location, otf2::definition::region region) : start(start),
                                                                                   end(anEnd),
                                                                                   location(std::move(location)),
                                                                                   region(std::move(region)) {}


Slot::Slot(const otf2::chrono::duration &start,otf2::definition::location location, otf2::definition::region region) : start(start),
                                                                                   location(std::move(location)),
                                                                                   region(std::move(region)) {}
