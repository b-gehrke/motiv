#ifndef MOTIV_FILETRACE_HPP
#define MOTIV_FILETRACE_HPP

#include "subtrace.hpp"

/**
 * Trace representing the whole trace loaded from trace files
 */
class FileTrace : public SubTrace {
private:
    std::vector<Slot>& slotsVec_;
    std::vector<Communication> &communicationsVec_;
public:
    /**
     * Creates a new instance
     *
     * @param slotss vector of all slots from the trace file
     * @param communications vector of communications from the trace file
     * @param runtime total runtime of the trace
     */
    FileTrace(std::vector<Slot>& slotss, std::vector<Communication> &communications, otf2::chrono::duration runtime);

    /**
     * @copydoc Trace::getSlots()
     */
    [[nodiscard]] Range<Slot> getSlots() const override;

    /**
     * @copydoc Trace::getCommunications()
     */
    [[nodiscard]] Range<Communication> getCommunications() const override;
};

#endif //MOTIV_FILETRACE_HPP
