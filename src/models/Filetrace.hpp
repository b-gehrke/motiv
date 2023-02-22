#ifndef MOTIV_FILETRACE_HPP
#define MOTIV_FILETRACE_HPP

#include "SubTrace.hpp"
#include "Range.hpp"

/**
 * Trace representing the whole trace loaded from trace files
 */
class FileTrace : public SubTrace {
private:
    std::vector<Slot *> slotsVec_;
    std::vector<Communication*> communications_;
    std::vector<CollectiveCommunicationEvent*> collectiveCommunications_;
public:
    /**
     * Creates a new instance
     *
     * @param slotss vector of all slots from the trace file
     * @param communications vector of communications from the trace file
     * @param runtime total runtime of the trace
     */
    FileTrace(std::vector<Slot*> &slotss,
              std::vector<Communication*> &communications,
              std::vector<CollectiveCommunicationEvent*> &collectiveCommunications_,
              otf2::chrono::duration runtime);

    virtual ~FileTrace();

    /**
     * @copydoc Trace::getSlots()
     */
    [[nodiscard]] std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> getSlots() const override;

    /**
     * @copydoc Trace::getCommunications()
     */
    [[nodiscard]] Range<Communication*> getCommunications() override;

    /**
     * @copydoc Trace::getCollectiveCommunications()
     */
    [[nodiscard]] Range<CollectiveCommunicationEvent*> getCollectiveCommunications() override;

};

#endif //MOTIV_FILETRACE_HPP
