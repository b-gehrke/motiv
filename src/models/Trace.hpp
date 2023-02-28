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
#ifndef MOTIV_TRACE_HPP
#define MOTIV_TRACE_HPP

#include <memory>
#include <vector>
#include <ranges>
#include "Slot.hpp"
#include "src/models/communication/Communication.hpp"
#include "src/models/communication/CollectiveCommunicationEvent.hpp"
#include "Range.hpp"
#include "TimedElement.hpp"


/**
 * @brief A comparator for otf2::definition::location_group objects
 */
struct LocationGroupCmp {
    /**
     * @brief Compares two otf2::definition::location_group objects
     *
     * @param l Left object
     * @param r Right object
     * @return True if l < r
     */
    bool operator()(const otf2::definition::location_group *l, const otf2::definition::location_group *r) const {
        return l->ref() < r->ref();
    }
};

/**
 * @brief Abstract base class for a trace.
 *
 * This class defines an abstract base class for a trace. It inherits from the TimedElement class and contains pure virtual functions that have to be implemented by derived classes.
 */
class Trace : public TimedElement {
public:
    /**
     * @brief Returns a map of slots of the current trace.
     *
     * This pure virtual function returns a map of slots of the current trace. The function has to be implemented in the derived classes.
     *
     * @return A map of slots of the current trace.
     */
    [[nodiscard]] virtual std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> getSlots() const = 0;

    /**
     * @brief Returns communication objects of the current trace.
     *
     * This pure virtual function returns communication objects of the current trace. The function has to be implemented in the derived classes.
     *
     * @return communication objects of the current trace.
     */
    [[nodiscard]] virtual Range<Communication*> getCommunications() = 0;

    /**
     * @brief Returns collective communication events of the current trace.
     *
     * This pure virtual function returns collective communication events of the current trace. The function has to be implemented in the derived classes.
     *
     * @return collective communication events of the current trace.
     */
    [[nodiscard]] virtual Range<CollectiveCommunicationEvent*> getCollectiveCommunications() = 0;

    /**
     * @brief Returns the runtime of the current trace.
     *
     * This pure virtual function returns the runtime of the current trace. The function has to be implemented in the derived classes.
     *
     * @return The runtime of the current trace.
     */
    [[nodiscard]] virtual otf2::chrono::duration getRuntime() const = 0;

    /**
     * @brief Creates a subtrace of the current trace.
     *
     * This pure virtual function creates a subtrace of the current trace by returning a new Trace object that only contains elements within the given time range. The function has to be implemented in the derived classes.
     *
     * @param from Time the the subtrace should start.
     * @param to Time the subtrace should end.
     * @return A new Trace object that only contains elements within the given time range.
     */
    [[nodiscard]] virtual Trace* subtrace(otf2::chrono::duration from, otf2::chrono::duration to) = 0;
};


#endif //MOTIV_TRACE_HPP
