#include <utility>

#include "./Slot.hpp"

Slot::Slot(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
           otf2::definition::location* location, otf2::definition::region* region) :
    startTime(start),
    endTime(anEnd),
    location(location),
    region(region) {
}

SlotKind Slot::getKind() const {
    auto regionName = this->region->name().str();
    if (regionName.starts_with("MPI_")) {
        return MPI;
    } else if (regionName.starts_with("!$omp")) {
        return OpenMP;
    } else {
        return Plain;
    }
}

types::TraceTime Slot::getStartTime() const {
    return startTime;
}

types::TraceTime Slot::getEndTime() const {
    return endTime;
}
