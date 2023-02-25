/*
 * Marvellous OTF2 Traces Interactive Visualizer (MOTIV)
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


struct LocationGroupCmp {
    bool operator()(const otf2::definition::location_group *l, const otf2::definition::location_group *r) const {
        return l->ref() < r->ref();
    }
};

class Trace : public TimedElement {
public:
    /**
     * Gets the slots
     * @return The slots
     */
    [[nodiscard]] virtual std::map<otf2::definition::location_group *, Range<Slot *>, LocationGroupCmp>
    getSlots() const = 0;

    [[nodiscard]] virtual Range<Communication *> getCommunications() = 0;

    [[nodiscard]] virtual Range<CollectiveCommunicationEvent *> getCollectiveCommunications() = 0;

    [[nodiscard]] virtual otf2::chrono::duration getRuntime() const = 0;

    [[nodiscard]] virtual Trace *subtrace(otf2::chrono::duration from, otf2::chrono::duration to) = 0;
};


#endif //MOTIV_TRACE_HPP
