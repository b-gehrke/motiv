#ifndef MOTIV_TIMEDELEMENT_HPP
#define MOTIV_TIMEDELEMENT_HPP

#include "src/types.h"

class TimedElement {
public:
    [[nodiscard]] virtual types::TraceTime getStartTime() const = 0;
    [[nodiscard]] virtual types::TraceTime getEndTime() const = 0;

    [[nodiscard]] virtual types::TraceTime getDuration() const { return getEndTime() - getStartTime(); }
};

#endif //MOTIV_TIMEDELEMENT_HPP
