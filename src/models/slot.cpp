#include <utility>

#include "./slot.hpp"

Slot::Slot(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
           otf2::definition::location* location, otf2::definition::region* region) :
    start(start),
    end(anEnd),
    location(location),
    region(region) {
}

SlotKind Slot::getKind() const {
    auto regionName = this->region->name().str();
    if(regionName.starts_with("MPI_")) {
        return MPI;
    } else if(regionName.starts_with("!$omp")) {
        return OpenMP;
    } else {
        return Plain;
    }
}
