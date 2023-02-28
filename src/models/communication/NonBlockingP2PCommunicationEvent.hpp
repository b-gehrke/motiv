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
#ifndef MOTIV_NONBLOCKINGP2PCOMMUNICATIONEVENT_HPP
#define MOTIV_NONBLOCKINGP2PCOMMUNICATIONEVENT_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "CommunicationEvent.hpp"
#include "CommunicationKind.hpp"
#include "src/types.hpp"
#include "src/models/Builder.hpp"

/**
 * @brief Class representing non blocking events in point to point communications like MPI_ISEND, MPI_IRECEIVE.
 *
 * This class bundles common functionality for these types of events and should be used as a base class and not
 * instantiated directly.
 */
class NonBlockingP2PCommunicationEvent : public CommunicationEvent {
protected:
    /**
     * Creates a new instance of the abstract NonBlockingP2PCommunicationEvent class.
     *
     * @param start Start time of the event
     * @param end End time of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    NonBlockingP2PCommunicationEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
                                     otf2::definition::location* location, types::communicator* communicator);

    otf2::chrono::duration start; /**< The time when the event started */
    otf2::chrono::duration end; /**< The time when the event ended */
    otf2::definition::location* location; /**< The location of the event */
    types::communicator* communicator; /**< The communicator of the operation */
public:

    /**
     * @copydoc CommunicationEvent::getLocation()
     */
    [[nodiscard]] otf2::definition::location * getLocation() const override;
    /**
     * @copydoc CommunicationEvent::getStartTime()
     */
    [[nodiscard]] otf2::chrono::duration getStartTime() const override;
    /**
     * @copydoc CommunicationEvent::getEndTime()
     */
    [[nodiscard]] otf2::chrono::duration getEndTime() const override;
    /**
     * @copydoc CommunicationEvent::getCommunicator()
     */
    [[nodiscard]] types::communicator * getCommunicator() const override;
};

#endif //MOTIV_NONBLOCKINGP2PCOMMUNICATIONEVENT_HPP
