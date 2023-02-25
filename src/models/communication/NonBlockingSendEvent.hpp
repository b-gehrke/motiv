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
#ifndef MOTIV_NONBLOCKINGSENDEVENT_HPP
#define MOTIV_NONBLOCKINGSENDEVENT_HPP


#include "NonBlockingP2PCommunicationEvent.hpp"

/**
 * Class representing the non blocking send event.
 */
class NonBlockingSendEvent : public NonBlockingP2PCommunicationEvent {
public:
    /**
     * Creates a new instance of the NonBlockingSendEvent class.
     *
     * @param start Start time of the event
     * @param end End time of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    NonBlockingSendEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
                         otf2::definition::location *location, types::communicator *communicator);

    CommunicationKind getKind() const override;


    BUILDER(NonBlockingSendEvent,
            BUILDER_FIELD(otf2::chrono::duration, start)
            BUILDER_FIELD(otf2::chrono::duration, end)
            BUILDER_FIELD(otf2::definition::location*, location)
            BUILDER_FIELD(types::communicator*, communicator)
            BUILDER_OPTIONAL_FIELD(uint32_t, receiver), // The receiver field is needed to match the receiving call. The
                                                        // location instance of the receiver is only known in the
                                                        // receive event.
            start, end, location, communicator)
};


#endif //MOTIV_NONBLOCKINGSENDEVENT_HPP
