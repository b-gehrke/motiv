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
#ifndef MOTIV_COMMUNICATION_HPP
#define MOTIV_COMMUNICATION_HPP

#include "src/models/Builder.hpp"
#include "src/types.hpp"
#include "CommunicationKind.hpp"
#include "CommunicationEvent.hpp"

#include "lib/otf2xx/include/otf2xx/otf2.hpp"

/**
 * Class representing any (successful or unsuccessful) communication.
 *
 * Each communication consists of two events: An event starting the communication and one ending it. A communication
 * does not have to successful. For example the end event might be of kind `RequestCancelled` indicating a request was not
 * completed.
 */
class Communication : public TimedElement {
public:
    /**
     * Creates a new instance of the `Communication` class
     * @param start The event initiating the communication
     * @param end The event ending the communication
     */
    Communication(const CommunicationEvent *start, const CommunicationEvent *end);

    /**
     * Gets the event that initiated the communication.
     * @return Event that initiated the communication
     */
    [[nodiscard]] const CommunicationEvent * getStartEvent() const;

    /**
     * Gets the event that ended the communication
     * @return event that ended the communication
     */
    [[nodiscard]] const CommunicationEvent * getEndEvent() const;

    types::TraceTime getStartTime() const override;

    types::TraceTime getEndTime() const override;

private:
    const CommunicationEvent* start;
    const CommunicationEvent* end;
};

#endif //MOTIV_COMMUNICATION_HPP
