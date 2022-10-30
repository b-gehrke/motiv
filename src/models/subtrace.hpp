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
     * @copydoc Trace::getRuntime()
     */
    [[nodiscard]] otf2::chrono::duration getRuntime() const override;

    /**
     * @copydoc Trace::subtrace()
     */
    [[nodiscard]] std::shared_ptr<Trace> subtrace(otf2::chrono::duration from, otf2::chrono::duration to) const override;


    /**
     * @copydoc Trace::getBlockingP2PCommunications()
     */
    [[nodiscard]] Range<BlockingP2PCommunication> getBlockingP2PCommunications() const override;


    /**
     * @copydoc Trace::getNonBlockingP2PCommunications()
     */
    [[nodiscard]] Range<NonBlockingP2PCommunication> getNonBlockingP2PCommunications() const override;


    /**
     * @copydoc Trace::getCollectiveCommunications()
     */
    [[nodiscard]] Range<CollectiveCommunication> getCollectiveCommunications() const override;


    /**
     * @copydoc Trace::getStartTime()
     */
    [[nodiscard]] otf2::chrono::duration getStartTime() const override;

protected:
    /**
     * Backing field for the range of slots of this subtrace
     */
    Range<Slot> slots_;

    /**
     * Backing field for blocking point-to-point communications of this subtrace
     */
    Range<BlockingP2PCommunication> blockingP2PCommunications_;

    /**
     * Backing field for non-blocking point-to-point communications of this subtrace
     */
    Range<NonBlockingP2PCommunication> nonBlockingP2PCommunications_;


    /**
     * Backing field for collective communications of this subtrace
     */
    Range<CollectiveCommunication> collectiveCommunications_;

    /**
     * Backing field for the runtime of this subtrace
     */
    otf2::chrono::duration runtime_{};

    /**
     * Backing field for the start time of this subtrace
     */
    otf2::chrono::duration startTime_{};
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

    SubTrace(const Range<Slot> &slots, const Range<BlockingP2PCommunication> &blockingP2PCommunications,
             const Range<NonBlockingP2PCommunication> &nonBlockingP2PCommunications,
             const Range<CollectiveCommunication> &collectiveCommunications, const otf2::chrono::duration &runtime,
             const otf2::chrono::duration &startTime);
};

#endif //MOTIV_SUBTRACE_HPP
