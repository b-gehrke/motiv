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
#include "./Communication.hpp"
#include "CommunicationKind.hpp"
#include "CommunicationEvent.hpp"
#include "BlockingP2PCommunicationEvent.hpp"

Communication::Communication(const CommunicationEvent *start, const CommunicationEvent *end) : start(start), end(end) {
}

const CommunicationEvent * Communication::getStartEvent() const {
    return start;
}

const CommunicationEvent * Communication::getEndEvent() const {
    return end;
}

types::TraceTime Communication::getStartTime() const {
    return start->getStartTime();
}

types::TraceTime Communication::getEndTime() const {
    return end->getEndTime();
}
