#ifndef MOTIV_SUBTRACE_HPP
#define MOTIV_SUBTRACE_HPP

#include "trace.hpp"


/**
 * Trace representing a section of a larger trace.
 */
class SubTrace : public Trace {
public:
    /**
     * @copydoc Trace::getSlots()
     */
    [[nodiscard]] Range<Slot> getSlots() const override;

    /**
     * @copydoc Trace::getCommunications()
     */
    [[nodiscard]] Range<Communication> getCommunications() const override;

    /**
     * @copydoc Trace::getRuntime()
     */
    [[nodiscard]] otf2::chrono::duration getRuntime() const override;

    /**
     * @copydoc Trace::subtrace()
     */
    [[nodiscard]] std::shared_ptr<Trace> subtrace(otf2::chrono::duration from, otf2::chrono::duration to) const override;

protected:
    /**
     * Backing field for the range of slots for this subtrace
     */
    Range<Slot> slots_;

    /**
     * Backing field for the range of slots for this communications_
     */
    Range<Communication> communications_;

    /**
     * Backing field for the range of slots for this runtime_
     */
    otf2::chrono::duration runtime_;
public:
    /**
     * Initializes an empty subtrace
     */
    SubTrace();

    /**
     * Initializes a new instance.
     *
     * @param slots Range of slots this subtrace covers
     * @param communications Range of communications this subtrace covers
     * @param runtime Runtime of this subtrace
     */
    SubTrace(const Range<Slot> &slots, const Range<Communication> &communications, otf2::chrono::duration runtime);
};

#endif //MOTIV_SUBTRACE_HPP
