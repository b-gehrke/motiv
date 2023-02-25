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
#ifndef MOTIV_COMMUNICATIONEVENT_HPP
#define MOTIV_COMMUNICATIONEVENT_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "CommunicationKind.hpp"
#include "src/types.h"
#include "src/models/Builder.hpp"
#include "src/models/TimedElement.hpp"

/**
 * Abstract class for generic Communication events. All communications handled by this application have a start and an
 * end event. See `Communication` for more details.
 */
class CommunicationEvent : public TimedElement {
public:
    /**
     * Gets the location of the recorded event.
     * @return Location of the recorded event
     */
    [[nodiscard]] virtual otf2::definition::location * getLocation() const = 0;

    /**
     * Gets the start time of the recorded event. The time is relative to the star time of the program.
     * @return Start time of the recorded event
     */
    [[nodiscard]] otf2::chrono::duration getStartTime() const override = 0;

    /**
     * Gets the end time of the recorded even. The time is relative to the star time of the program.
     * @return End time of the recorded event
     */
    [[nodiscard]] otf2::chrono::duration getEndTime() const override = 0;

    /**
     * Gets the communicator the recorded event took place in.
     * @return Communicator of the event
     */
    [[nodiscard]] virtual types::communicator * getCommunicator() const = 0;

    /**
     * Gets the kind of communication event. Implemented by each derived class.
     * @return Kind of event.
     */
    [[nodiscard]] virtual CommunicationKind getKind() const = 0;
};

#endif //MOTIV_COMMUNICATIONEVENT_HPP
