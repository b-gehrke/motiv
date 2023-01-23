#ifndef MOTIV_UITRACE_HPP
#define MOTIV_UITRACE_HPP


#include <utility>

#include "subtrace.hpp"

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
            const otf2::chrono::duration &timePerPx) :
        SubTrace(),
        timePerPx_(timePerPx),
        slotsVec_(std::move(slotsVec)) {
        communications_ = communications;
        collectiveCommunications_ = collectiveCommunications;
        runtime_ = runtime;
        startTime_ = startTime;

        for (auto &item: slotsVec_) {
            slots_.insert({item.first, Range(item.second)});
        }
    }

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
    static UITrace *forResolution(Trace *trace, otf2::chrono::duration timePerPixel) {
        auto minDuration = timePerPixel * MIN_SLOT_SIZE_PX;
        std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> groupedSlots;
        std::map<otf2::definition::location_group *, Range<Slot *>, LocationGroupCmp> groupedSlotsRange;

        for (const auto &item: trace->getSlots()) {
            auto locationGroup = item.first;
            auto slots = item.second;
            std::vector<Slot *> newSlots;

            Slot *intervalStarter = nullptr;
            std::map<SlotKind, std::vector<Slot *>> *stats = nullptr;


            for (const auto &slot: slots) {
                if (intervalStarter != nullptr && (slot->start > intervalStarter->start + minDuration)) {
                    Slot *newSlot;
                    // Order of importance if overlapping, the slot with the most important kind is shown.
                    // 1. MPI events, 2. OpenMP events 3. all other events
                    if (stats->contains(MPI)) {
                        auto mpiStats = stats->at(MPI);
                        newSlot = aggregateSlots(minDuration, intervalStarter, mpiStats);
                    } else if (stats->contains(OpenMP)) {
                        auto openMpStats = stats->at(OpenMP);
                        newSlot = aggregateSlots(minDuration, intervalStarter, openMpStats);
                    } else {
                        auto plainStats = stats->at(Plain);
                        newSlot = aggregateSlots(minDuration, intervalStarter, plainStats);
                    }

                    delete stats;
                    stats = nullptr;
                    intervalStarter = nullptr;

                    newSlots.push_back(newSlot);
                }

                if (slot->getDuration() < minDuration) {
                    if (intervalStarter == nullptr) {
                        intervalStarter = slot;
                        stats = new std::map<SlotKind, std::vector<Slot *>>();
                    }

                    if (!stats->contains(slot->getKind())) {
                        stats->insert({slot->getKind(), std::vector<Slot *>()});
                    }

                    stats->at(slot->getKind()).push_back(slot);
                } else {
                    newSlots.push_back(slot);
                }
            }


            groupedSlots.insert({locationGroup, newSlots});
        }

        return new UITrace(groupedSlots, trace->getCommunications(), trace->getCollectiveCommunications(),
                           trace->getRuntime(), trace->getStartTime(), timePerPixel);
    }

    static Slot *
    aggregateSlots(otf2::chrono::duration minDuration, const Slot *intervalStarter, std::vector<Slot *> &stats) {
        Slot *longestSlot = *std::max_element(stats.begin(), stats.end(), [](Slot *lhs, Slot *rhs) {
            return lhs->getDuration() > rhs->getDuration();
        });

        return new Slot(intervalStarter->start, intervalStarter->start + minDuration, longestSlot->location,
                        longestSlot->region);
    }

    Trace *subtrace(otf2::chrono::duration from, otf2::chrono::duration to) override {
        return forResolution(SubTrace::subtrace(from, to), timePerPx_);
    }

private:
    otf2::chrono::duration timePerPx_;
    std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> slotsVec_;
};

#endif //MOTIV_UITRACE_HPP
