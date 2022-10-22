#ifndef MOTIV_SUBTRACE_HPP
#define MOTIV_SUBTRACE_HPP

#include "trace.hpp"


class SubTrace : public Trace {
public:
    [[nodiscard]] Range<Slot> getSlots() const override;

    [[nodiscard]] Range<Communication> getCommunications() const override;

    [[nodiscard]] otf2::chrono::duration getRuntime() const override;

    [[nodiscard]] std::shared_ptr<Trace> subtrace(otf2::chrono::duration from, otf2::chrono::duration to) const override;

protected:
    Range<Slot> slots_;
    Range<Communication> communications_;
    otf2::chrono::duration runtime_;
public:
    SubTrace();
    SubTrace(const Range<Slot> &slots, const Range<Communication> &communications, otf2::chrono::duration runtime);
};

#endif //MOTIV_SUBTRACE_HPP
