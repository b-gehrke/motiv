#ifndef MOTIV_TRACE_HPP
#define MOTIV_TRACE_HPP

#include <memory>
#include <vector>
#include <ranges>
#include "slot.hpp"
#include "src/models/communication/communication.hpp"
#include "src/models/communication/collectivecommunicationevent.hpp"

template <typename T>
struct Range {
    using It = typename std::vector<T>::iterator;


    It begin_;
    It end_;

    Range() = default;
    Range(It begin, It end) : begin_(begin), end_(end) {};
    explicit Range(std::vector<T>& vec) : begin_(vec.begin()), end_(vec.end()) {};
//    explicit Range(const std::vector<Slot>& vec) : begin_(vec.begin()), end_(vec.end()) {};

    It begin() const { return begin_; }
    It end() const { return end_; }

    [[nodiscard]] bool empty() const { return begin_ == end_; }
};


struct LocationGroupCmp {
    bool operator ()(const otf2::definition::location_group* l, const otf2::definition::location_group* r) const {
        return l->ref() < r->ref();
    }
};

class Trace {
public:
    /**
     * Gets the slots
     * @return The slots
     */
    [[nodiscard]] virtual std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> getSlots() const = 0;
    [[nodiscard]] virtual Range<Communication*> getCommunications() = 0;
    [[nodiscard]] virtual Range<CollectiveCommunicationEvent*> getCollectiveCommunications() = 0;
    [[nodiscard]] virtual otf2::chrono::duration getStartTime() const = 0;
    [[nodiscard]] virtual otf2::chrono::duration getRuntime() const = 0;

    [[nodiscard]] virtual Trace* subtrace(otf2::chrono::duration from, otf2::chrono::duration to) = 0;
};


#endif //MOTIV_TRACE_HPP
