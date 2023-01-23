#ifndef MOTIV_TRACE_HPP
#define MOTIV_TRACE_HPP

#include <memory>
#include <vector>
#include <ranges>
#include "slot.hpp"
#include "src/models/communication/communication.hpp"
#include "src/models/communication/collectivecommunicationevent.hpp"

template<typename T>
class Range {
public:
    using It = typename std::vector<T>::iterator;

    Range() = default;

    Range(It begin, It end) : begin_(begin), end_(end), vec_(nullptr) {};

    Range (const Range& rhs) {
        if(rhs.vec_) {
            vec_ = new std::vector<T>(*rhs.vec_);
            begin_ = std::find(vec_->begin(), vec_->end(), *rhs.begin_);
            end_ = std::find(vec_->begin(), vec_->end(), *rhs.end_);
        } else {
            begin_ = rhs.begin_;
            end_ = rhs.end_;
        }
    };

    Range<T>& operator=(const Range<T>& rhs) {
        if(this == &rhs){
            return *this;
        }


        if(rhs.vec_) {
            delete vec_;
            vec_ = new std::vector<T>(*rhs.vec_);
            begin_ = std::find(vec_->begin(), vec_->end(), *rhs.begin_);
            end_ = std::find(vec_->begin(), vec_->end(), *rhs.end_);
        } else {
            begin_ = rhs.begin_;
            end_ = rhs.end_;
        }

        return *this;
    }

    /**
     * Construct a range from a vector.
     *
     * Copies the vector.
     * @param vec
     */
    explicit Range(std::vector<T> &vec) : vec_(new std::vector<T>(vec)), begin_(vec_->begin()), end_(vec_->end()) {};

    /**
     * Iterator to the beginning of the range
     * @return
     */
    It begin() const { return begin_; }


    /**
     * Iterator to the end of the range
     * @return
     */
    It end() const { return end_; }

    [[nodiscard]] bool empty() const { return begin_ == end_; }



    virtual ~Range() {
        delete vec_;
    }

private:
    std::vector<T> *vec_ = nullptr;
    It begin_;
    It end_;
};


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
