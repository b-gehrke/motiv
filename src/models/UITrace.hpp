#ifndef MOTIV_UITRACE_HPP
#define MOTIV_UITRACE_HPP


#include <utility>

#include "SubTrace.hpp"
#include "Range.hpp"

/**
 * Defines the minimum size in pixels for a slot
 */
#define MIN_SLOT_SIZE_PX 2

/**
 * Trace facilitating a subtrace optimized for rendering
 *
 * Slots that would be rendered smaller than `MIN_SLOT_SIZE_PX` pixels are grouped together to a single slot.
 * Instead of all slots that fit inside `MIN_SLOT_SIZE_PX` the longest slot with the most important kind is shown.
 */
class UITrace : public SubTrace {
private:
    /**
     * Creates a new instance of the `UITrace` class.
     *
     * @param slotsVec vectors of grouped slots
     * @param communications range of communications
     * @param collectiveCommunications range of collective communications
     * @param runtime runtime of the trace
     * @param startTime starttime of the trace
     * @param timePerPx duration that fits into one pixel
     */
    UITrace(std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> slotsVec,
            const Range<Communication *> &communications,
            const Range<CollectiveCommunicationEvent *> &collectiveCommunications,
            const otf2::chrono::duration &runtime, const otf2::chrono::duration &startTime,
            const otf2::chrono::duration &timePerPx);

public:
    /**
     * Wraps a trace into a UITrace optimized for rendering performance.
     *
     * @seealso UITrace
     *
     * @param trace original trace to be optimized
     * @param timePerPx duration that fits into one pixel
     * @return the UITrace wrapping the original trace
     */
    static UITrace *forResolution(Trace *trace, otf2::chrono::duration timePerPixel);

    Trace *subtrace(otf2::chrono::duration from, otf2::chrono::duration to) override;

private:
    otf2::chrono::duration timePerPx_;
    std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> slotsVec_;

    /**
     * Aggregates slots in an interval into a new summarized slot.
     *
     * Creates a new slot representing all slots in @c stats
     * @param minDuration Minimum duration for the new slot
     * @param intervalStarter First slot in the interval
     * @param stats All other slots in this interval
     * @return A new slot summarizing all slots in the interval
     */
    static Slot *
    aggregateSlots(otf2::chrono::duration minDuration, const Slot *intervalStarter, std::vector<Slot *> &stats);
};

#endif //MOTIV_UITRACE_HPP
