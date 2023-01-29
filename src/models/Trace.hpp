#ifndef MOTIV_TRACE_HPP
#define MOTIV_TRACE_HPP

#include <memory>
#include <vector>
#include <ranges>
#include "Slot.hpp"
#include "src/models/communication/Communication.hpp"
#include "src/models/communication/CollectiveCommunicationEvent.hpp"
#include "Range.hpp"


struct LocationGroupCmp {
    bool operator()(const otf2::definition::location_group *l, const otf2::definition::location_group *r) const {
        return l->ref() < r->ref();
    }
};

class Trace {
public:
    /**
     * Gets the slots
     * @return The slots
     */
    [[nodiscard]] virtual std::map<otf2::definition::location_group *, Range<Slot *>, LocationGroupCmp>
    getSlots() const = 0;

[[nodiscard]] virtual Range<Communication *> getCommunications() = 0;

    [[nodiscard]] virtual Range<CollectiveCommunicationEvent *> getCollectiveCommunications() = 0;

    [[nodiscard]] virtual otf2::chrono::duration getStartTime() const = 0;

    [[nodiscard]] virtual otf2::chrono::duration getRuntime() const = 0;

    [[nodiscard]] virtual Trace *subtrace(otf2::chrono::duration from, otf2::chrono::duration to) = 0;
};


#endif //MOTIV_TRACE_HPP
