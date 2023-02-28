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
#ifndef MOTIV_BLOCKINGRECEIVEEVENT_HPP
#define MOTIV_BLOCKINGRECEIVEEVENT_HPP


#include "BlockingP2PCommunicationEvent.hpp"

/**
 * @brief Class representing the blocking send event.
 */
class BlockingReceiveEvent : public BlockingP2PCommunicationEvent {
public:
    /**
     * Creates a new instance of the BlockingReceiveEvent class.
     *
     * @param timepoint Timepoint of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    BlockingReceiveEvent(const otf2::chrono::duration &timepoint, otf2::definition::location *location,
                         types::communicator *communicator);

    CommunicationKind getKind() const override;
};


#endif //MOTIV_BLOCKINGRECEIVEEVENT_HPP
