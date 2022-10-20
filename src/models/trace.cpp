#include "trace.hpp"

#include <utility>

Trace::Trace(std::shared_ptr<std::vector<Slot>> slotss,
             std::shared_ptr<std::vector<Communication>> communications, const otf2::chrono::duration &runtime)
    : slotss(std::move(slotss)), communications(std::move(communications)), runtime(runtime) {}
