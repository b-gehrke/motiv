#ifndef MOTIV_FILETRACE_HPP
#define MOTIV_FILETRACE_HPP

#include "subtrace.hpp"

/**
 * Trace representing the whole trace loaded from trace files
 */
class FileTrace : public SubTrace {
private:
    std::vector<Slot> &slots_;
    std::vector<BlockingP2PCommunication> &blockingComm_;
    std::vector<NonBlockingP2PCommunication> &nonBlockingComm_;
    std::vector<CollectiveCommunication> &collectiveComm_;
public:
    /**
     * Creates a new instance
     *
     * @param slotss vector of all slots from the trace file
     * @param communications vector of communications from the trace file
     * @param runtime total runtime of the trace
     */
    FileTrace(std::vector<Slot> &slotss,
              std::vector<BlockingP2PCommunication> &blockingComm,
              std::vector<NonBlockingP2PCommunication> &nonBlockingComm,
              std::vector<CollectiveCommunication> &collectiveComm,
              otf2::chrono::duration runtime);

    /**
     * @copydoc Trace::getSlots()
     */
    [[nodiscard]] Range<Slot> getSlots() const override;

    [[nodiscard]] Range<BlockingP2PCommunication> getBlockingP2PCommunications() const override;

    [[nodiscard]] Range<NonBlockingP2PCommunication> getNonBlockingP2PCommunications() const override;

    [[nodiscard]] Range<CollectiveCommunication> getCollectiveCommunications() const override;
};

#endif //MOTIV_FILETRACE_HPP
