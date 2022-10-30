#ifndef MOTIV_TRACE_HPP
#define MOTIV_TRACE_HPP

#include <memory>
#include <vector>
#include <ranges>
#include "slot.hpp"
#include "communication.hpp"
#include "blockingp2pcommunication.hpp"
#include "nonblockingp2pcommunication.hpp"
#include "collectivecommunication.hpp"

template <typename T>
struct Range {
    using It = typename std::vector<T>::iterator;

    It begin_;
    It end_;

    Range() = default;
    Range(It begin, It end) : begin_(begin), end_(end) {};
    explicit Range(std::vector<T>& vec) : begin_(vec.begin()), end_(vec.end()) {};

    It begin() const { return begin_; }
    It end() const { return end_; }

    [[nodiscard]] bool empty() const { return begin_ == end_; }
};

class Trace {
public:
    /**
     * Gets the slots
     * @return The slots
     */
    [[nodiscard]] virtual Range<Slot> getSlots() const = 0;
    [[nodiscard]] virtual Range<BlockingP2PCommunication> getBlockingP2PCommunications() const = 0;
    [[nodiscard]] virtual Range<NonBlockingP2PCommunication> getNonBlockingP2PCommunications() const = 0;
    [[nodiscard]] virtual Range<CollectiveCommunication> getCollectiveCommunications() const = 0;
    [[nodiscard]] virtual otf2::chrono::duration getStartTime() const = 0;
    [[nodiscard]] virtual otf2::chrono::duration getRuntime() const = 0;

    [[nodiscard]] virtual std::shared_ptr<Trace> subtrace(otf2::chrono::duration from, otf2::chrono::duration to) const = 0;
};


#endif //MOTIV_TRACE_HPP
