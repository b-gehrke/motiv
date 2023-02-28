/*
 * Marvelous OTF2 Traces Interactive Visualizer (MOTIV)
 * Copyright (C) 2023 Florian Gallrein, Björn Gehrke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MOTIV_RANGE_HPP
#define MOTIV_RANGE_HPP

#include "src/models/communication/CollectiveCommunicationEvent.hpp"
#include "src/models/communication/Communication.hpp"
#include "Slot.hpp"
#include <ranges>
#include <vector>
#include <memory>

/**
 * @brief A custom range implementation around std::vector<T>s
 *
 * An instance can be created as a copy of a vector or just with to iterators. This allows a more efficient way to pass
 * sub ranges around.
 *
 * @tparam T Type of element
 */
template<typename T>
class Range {
public:
    /**
     * @brief Shortcut for the iterator
     */
    using It = typename std::vector<T>::iterator;

    /**
     * @brief Creates an empty range
     */
    Range() = default;

    /**
     * @brief Creates a Range defined by two iterators.
     * @param begin Iterator pointing to the begin of the range.
     * @param end Iterator pointing to one past the last element of the range.
     */
    Range(It begin, It end) : begin_(begin), end_(end), vec_(nullptr) {};

    /**
     * @brief Constructs a new Range object from a given Range object.
     *
     * @param rhs The Range object to copy from.
     */
    Range(const Range &rhs) {
        if (rhs.vec_) {
            vec_ = new std::vector<T>(*rhs.vec_);
            begin_ = std::find(vec_->begin(), vec_->end(), *rhs.begin_);
            end_ = std::find(vec_->begin(), vec_->end(), *rhs.end_);
        } else {
            begin_ = rhs.begin_;
            end_ = rhs.end_;
        }
    };

    /**
     * Construct a range from a vector.
     *
     * Copies the vector.
     * @param vec
     */
    explicit Range(std::vector<T> &vec) : vec_(new std::vector<T>(vec)), begin_(vec_->begin()), end_(vec_->end()) {};

public:
    /**
     * @brief Copy assignment constructor.
     *
     * If the right hand side was constructed from a vector it is copied as well and the original vector is deleted.
     * Otherwise the ranges are copied.
     *
     * @param rhs Right hand side of the assignment
     * @return The copied element
     */
    Range<T> &operator=(const Range<T> &rhs) {
        if (this == &rhs) {
            return *this;
        }


        if (rhs.vec_) {
            delete vec_;
            vec_ = new std::vector<T>(*rhs.vec_);
            begin_ = std::find(vec_->begin(), vec_->end(), *rhs.begin_);
            end_ = std::find(vec_->begin(), vec_->end(), *rhs.end_);
        } else {
            begin_ = rhs.begin_;
            end_ = rhs.end_;
        }

        return *this;
    };


    /**
     * Iterator to the beginning of the range
     * @return
     */
    It begin() const { return begin_; };


    /**
     * Iterator to the end of the range
     * @return
     */
    It end() const { return end_; };

    /**
     * Whether the range contains no elements
     * @return true if the range is empty
     */
    [[nodiscard]] bool empty() const { return begin_ == end_; };

    virtual ~Range() {
        delete vec_;
    };

private:
    std::vector<T> *vec_ = nullptr;
    It begin_;
    It end_;
};

#endif //MOTIV_RANGE_HPP
