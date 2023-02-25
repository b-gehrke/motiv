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

#include <chrono>
#include "otf2xx/definition/location.hpp"
#include "NonBlockingP2PCommunicationEvent.hpp"

NonBlockingP2PCommunicationEvent::NonBlockingP2PCommunicationEvent(const otf2::chrono::duration &start,
                                                                   const otf2::chrono::duration &end,
                                                                   otf2::definition::location *location,
                                                                   types::communicator *communicator)
        : start(start), end(end), location(location), communicator(communicator) {}

otf2::definition::location * NonBlockingP2PCommunicationEvent::getLocation() const {
    return location;
}

otf2::chrono::duration NonBlockingP2PCommunicationEvent::getStartTime() const {
    return start;
}

otf2::chrono::duration NonBlockingP2PCommunicationEvent::getEndTime() const {
    return end;
}

types::communicator * NonBlockingP2PCommunicationEvent::getCommunicator() const {
    return communicator;
}
