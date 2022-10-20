#ifndef MOTIV_TRACE_HPP
#define MOTIV_TRACE_HPP

#include <memory>
#include "slot.hpp"
#include "communication.hpp"

class Trace {
public:
    Trace(std::shared_ptr<std::vector<Slot>> slotss,
          std::shared_ptr<std::vector<Communication>> communications, const otf2::chrono::duration &runtime);

    std::shared_ptr<std::vector<Slot>> slotss;
    std::shared_ptr<std::vector<Communication>> communications;

    otf2::chrono::duration runtime;
};

#endif //MOTIV_TRACE_HPP
