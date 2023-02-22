#include "UITrace.hpp"
#include "src/utils.hpp"

#include <QDebug>

UITrace::UITrace(std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> slotsVec,
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

UITrace *UITrace::forResolution(Trace *trace, otf2::chrono::duration timePerPixel) {
    auto minDuration = timePerPixel * MIN_SLOT_SIZE_PX;
    std::map<otf2::definition::location_group *, std::vector<Slot *>, LocationGroupCmp> groupedSlots;

    for (const auto &item: trace->getSlots()) {
        auto locationGroup = item.first;
        auto slots = item.second;
        qDebug() << "Rank" << locationGroup->name().str().c_str();

        qDebug() << "Slots" << std::distance(slots.begin(), slots.end());

        auto newSlots = optimize<Slot, SlotKind>(minDuration,
                                                 slots,
                                                 &Slot::getKind,
                                                 UITrace::slotInterval);


        qDebug() << "New slots" << newSlots.size();
        groupedSlots.insert({locationGroup, newSlots});
    }


    minDuration = timePerPixel * MIN_COMMUNICATION_SIZE_PX;
    auto communicationsByRank = groupBy<Communication *, otf2::reference<otf2::definition::location_group>>(
        trace->getCommunications(),
        [](const Communication *c) { return c->getStartEvent()->getLocation()->location_group().ref(); },
        [](const Communication *l, const Communication *r) {
            auto rankL = l->getStartEvent()->getLocation()->location_group().ref();
            auto rankR = r->getStartEvent()->getLocation()->location_group().ref();

            if (rankL == rankR) {
                return l->getStartTime() < r->getStartTime();
            }

            return rankL < rankR;
        });

    std::vector<Communication *> newCommunications;
    for (const auto &item: communicationsByRank) {
        auto comms = item.second;
        auto newCommunicationsForRank = optimize<Communication>(
            minDuration,
            comms,
            [](types::TraceTime, Communication *starter, std::vector<Communication *> &) { return starter; });
        newCommunications.insert(newCommunications.end(), newCommunicationsForRank.begin(), newCommunicationsForRank.end());
    }


    minDuration = timePerPixel * MIN_COLLECTIVE_EVENT_SIZE_PX;

    auto newCollectiveCommunications = optimize<CollectiveCommunicationEvent>(minDuration, trace->getCollectiveCommunications(),
                                                        &UITrace::aggregateCollectiveCommunications);

    return new UITrace(groupedSlots, Range(newCommunications), Range(newCollectiveCommunications),
                       trace->getRuntime(), trace->getStartTime(), timePerPixel);
}

template<class T>
requires std::is_base_of_v<TimedElement, T>
std::vector<T *> UITrace::optimize(types::TraceTime minDuration,
                                   Range<T *> elements,
                                   std::function<T *(types::TraceTime, T *, std::vector<T *> &stats)> aggregate) {
    return optimize<T, uint8_t>(
        minDuration,
        elements,
        [](const T *) { return 0; },
        [aggregate](types::TraceTime minDuration, T *starter, std::map<uint8_t, std::vector<T *>> &stats) {
            return aggregate(minDuration, starter, stats[0]);
        });
}

template<class T, typename K>
requires std::is_base_of_v<TimedElement, T>
std::vector<T *> UITrace::optimize(types::TraceTime minDuration,
                                   Range<T *> &elements,
                                   std::function<K(const T *)> keySelector,
                                   std::function<T *(types::TraceTime, T *,
                                                     std::map<K, std::vector<T *>> &stats)> aggregate) {
    std::vector<T *> newElements;
    T *intervalStarter = nullptr;
    std::map<K, std::vector<T *>> stats;

    for (const auto &element: elements) {
        if (intervalStarter != nullptr && (element->getStartTime() > intervalStarter->getStartTime() + minDuration)) {
            newElements.push_back(aggregate(minDuration, intervalStarter, stats));
//            qDebug() << "Inserted aggregated element";

            stats.clear();
            intervalStarter = nullptr;
        }

        if (element->getDuration() < minDuration) {
            if (intervalStarter == nullptr) {
                intervalStarter = element;
            }

            if (!stats.contains(keySelector(element))) {
                stats.insert({keySelector(element), std::vector<T *>()});
            }

            stats.at(keySelector(element)).push_back(element);
        } else {
            newElements.push_back(element);
//            qDebug() << "Inserted element";
        }
    }
    if (intervalStarter) {
        newElements.push_back(aggregate(minDuration, intervalStarter, stats));
//        qDebug() << "Inserted last aggregated element";
    }
    return newElements;
}

Slot *UITrace::slotInterval(types::TraceTime minDuration, const Slot *intervalStarter,
                            std::map<SlotKind, std::vector<Slot *>> &stats) {
    Slot *newSlot;
    // Order of importance if overlapping, the slot with the most important kind is shown.
// 1. MPI events, 2. OpenMP events 3. all other events
    if (stats.contains(MPI)) {
        auto mpiStats = stats.at(MPI);
        newSlot = aggregateSlots(minDuration, intervalStarter, mpiStats);
    } else if (stats.contains(OpenMP)) {
        auto openMpStats = stats.at(OpenMP);
        newSlot = aggregateSlots(minDuration, intervalStarter, openMpStats);
    } else {
        auto plainStats = stats.at(Plain);
        newSlot = aggregateSlots(minDuration, intervalStarter, plainStats);
    }
    return newSlot;
}

Trace *UITrace::subtrace(otf2::chrono::duration from, otf2::chrono::duration to) {
    return forResolution(SubTrace::subtrace(from, to), timePerPx_);
}


template<class T>
requires std::is_base_of_v<TimedElement, T>
static T *longest(std::vector<T *> ls) {
    return *std::max_element(ls.begin(), ls.end(), [](T *lhs, T *rhs) {
        return lhs->getDuration() > rhs->getDuration();
    });
}

template<class T>
requires std::is_base_of_v<TimedElement, T>
static T *last(std::vector<T *> ls) {
    return *std::max_element(ls.begin(), ls.end(), [](T *lhs, T *rhs) {
        return lhs->getEndTime() < rhs->getEndTime();
    });
}


Slot *UITrace::aggregateSlots(otf2::chrono::duration minDuration,
                              const Slot *intervalStarter,
                              std::vector<Slot *> &stats) {
    auto longestSlot = longest(stats);
    auto intervalEnder = last(stats);

    return new Slot(intervalStarter->startTime, intervalEnder->endTime, longestSlot->location, longestSlot->region);
}

UITrace *UITrace::forResolution(Trace *trace, int width) {
    return forResolution(trace, trace->getRuntime() / width);
}

CollectiveCommunicationEvent *UITrace::aggregateCollectiveCommunications(otf2::chrono::duration minDuration,
                                                                         const CollectiveCommunicationEvent *intervalStarter,
                                                                         std::vector<CollectiveCommunicationEvent *> &stats) {
    auto longestEvent = longest(stats);
    auto intervalEnder = last(stats);

    auto singleMember = new CollectiveCommunicationEvent::Member(intervalStarter->getStartTime(),
                                                                 intervalEnder->getEndTime(),
                                                                 longestEvent->getLocation());

    std::vector<CollectiveCommunicationEvent::Member *> singletonMembers;
    singletonMembers.push_back(singleMember);

    return new CollectiveCommunicationEvent(
        singletonMembers, longestEvent->getLocation(), longestEvent->getCommunicator(),
        longestEvent->getOperation(), longestEvent->getRoot()
    );
}
