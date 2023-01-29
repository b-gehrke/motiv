#ifndef MOTIV_SUBTRACE_HPP
#define MOTIV_SUBTRACE_HPP

#include "Trace.hpp"
#include "Range.hpp"


/**
 * Trace representing a section of a larger trace.
 */
class SubTrace : public Trace {
public:
    /**
     * @copydoc Trace::getSlots()
     */
    [[nodiscard]] std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> getSlots() const override;

    /**
     * @copydoc Trace::getRuntime()
     */
    [[nodiscard]] otf2::chrono::duration getRuntime() const override;

    /**
     * @copydoc Trace::subtrace()
     */
    [[nodiscard]] Trace* subtrace(otf2::chrono::duration from, otf2::chrono::duration to) override;

    /**
     * @copydoc Trace::getCommunications()
     */
    [[nodiscard]] Range<Communication*> getCommunications() override;


    /**
     * @copydoc Trace::getCommunications()
     */
    [[nodiscard]] Range<CollectiveCommunicationEvent*> getCollectiveCommunications() override;


    /**
     * @copydoc Trace::getStartTime()
     */
    [[nodiscard]] otf2::chrono::duration getStartTime() const override;

protected:
    /**
     * Backing field for the range of slots of this subtrace
     */
    std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> slots_;

    /**
     * Backing field for communications of this subtrace
     */
    Range<Communication*> communications_;

    /**
     * Backing field for collective communications of this subtrace
     */
    Range<CollectiveCommunicationEvent*> collectiveCommunications_;

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
    SubTrace(std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> &slots,
             const Range<Communication*> &communications,
             const Range<CollectiveCommunicationEvent*> &collectiveCommunications,
             const otf2::chrono::duration &runtime,
             const otf2::chrono::duration &startTime);
};

#endif //MOTIV_SUBTRACE_HPP
