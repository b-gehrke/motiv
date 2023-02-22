#ifndef MOTIV_UITRACE_HPP
#define MOTIV_UITRACE_HPP


#include <utility>

#include "SubTrace.hpp"
#include "Range.hpp"

/**
 * Defines the minimum size in pixels for a slot
 */
#define MIN_SLOT_SIZE_PX 5

/**
 * Defines the minimum size in pixels for a communication
 */
#define MIN_COMMUNICATION_SIZE_PX 15

/**
 * Defines the minimum size in pixels for a collective communication event
 */
#define MIN_COLLECTIVE_EVENT_SIZE_PX 10

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


    /**
     * Wraps a trace into a UITrace optimized for rendering performance.
     *
     * @seealso UITrace
     *
     * @param trace original trace to be optimized
     * @param width the width in px for which the trace should be optimized
     * @return the UITrace wrapping the original trace
     */
    static UITrace *forResolution(Trace *trace, int width);

    /**
     * @copydoc Trace::subtrace()
     */
    Trace *subtrace(otf2::chrono::duration from, otf2::chrono::duration to) override;

private:
    /**
     * Backing field. Stores the time that can be represented per pixel.
     */
    otf2::chrono::duration timePerPx_;

    /**
     * Aggregates slots in an interval into a new summarized slot.
     *
     * Creates a new slot representing all slots in @c stats
     * @param intervalStarter First slot in the interval
     * @param stats All other slots in this interval
     * @return A new slot summarizing all slots in the interval
     */
    static Slot *
    aggregateSlots(const Slot *intervalStarter, std::vector<Slot *> &stats);

    /**
     * Aggregates collective communications in an interval into a new summarized collective communication event.
     *
     * Creates a new collective communication event representing all events in @c stats
     * @param intervalStarter First event in the interval
     * @param stats All other events in this interval
     * @return A new collective communication event summarizing all events in the interval
     */
    static CollectiveCommunicationEvent *
    aggregateCollectiveCommunications(const CollectiveCommunicationEvent *intervalStarter,
                                      std::vector<CollectiveCommunicationEvent *> &stats);

    /**
     * Aggregates slots in an interval respecting stats
     *
     * Creates a new slot representing all slots in {@c stats} by ordering them by priority with their kind
     * @param intervalStarter First slot in the interval
     * @param stats All other slots grouped by kind in the interval
     * @return A new slot summarizing all slots in the interval
     */
    static Slot *slotInterval(const Slot *intervalStarter, std::map<SlotKind, std::vector<Slot *>> &stats);

    /**
     * Collects and optimizes timed elements to small to be rendered.
     * @tparam T Type of {@c TimedElement}
     * @param minDuration Minimum duration of a {@c TimedElement} to be rendered
     * @param elements All elements to be rendered
     * @param aggregate Function to aggregate multiple elements into one
     * @return @c elements but to short element are summarized
     */
    template<class T>
    requires std::is_base_of_v<TimedElement, T>
    static std::vector<T *> optimize(
        types::TraceTime minDuration,
        Range<T *> elements,
        std::function<T *(T *, std::vector<T *> &stats)> aggregate);

    /**
     * Collects and optimizes timed elements to small to be rendered.
     *
     * Elements in one interval (shortest render time) are grouped with a function @c keySelector. The resulting map is
     * passed to @c aggregate
     * @tparam T Type of {@c TimedElement}
     * @tparam K Type of group by key
     * @param minDuration Minimum duration of a {@c TimedElement} to be rendered
     * @param elements All elements to be rendered
     * @param keySelector Function to select a key to group by
     * @param aggregate Function to aggregate multiple elements into one
     * @return @c elements but to short element are summarized
     */
    template<class T, typename K>
    requires std::is_base_of_v<TimedElement, T>
    static std::vector<T *> optimize(
        types::TraceTime minDuration,
        Range<T *> &elements,
        std::function<K(const T *)> keySelector,
        std::function<T *(T *, std::map<K, std::vector<T *>> &stats)> aggregate);
};

#endif //MOTIV_UITRACE_HPP
