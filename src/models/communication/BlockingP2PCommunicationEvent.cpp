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
#include <utility>

#include "./BlockingP2PCommunicationEvent.hpp"

BlockingP2PCommunicationEvent::BlockingP2PCommunicationEvent(const otf2::chrono::duration &timepoint,
                                                             otf2::definition::location* location,
                                                             types::communicator* communicator) : timepoint(
    timepoint), location(location), communicator(communicator) {}

otf2::chrono::duration BlockingP2PCommunicationEvent::getStartTime() const {
    return timepoint;
}

otf2::definition::location * BlockingP2PCommunicationEvent::getLocation() const {
    return location;
}

otf2::chrono::duration BlockingP2PCommunicationEvent::getEndTime() const {
    return timepoint + BLOCKING_EVENT_DURATION;
}

types::communicator * BlockingP2PCommunicationEvent::getCommunicator() const {
    return communicator;
}



