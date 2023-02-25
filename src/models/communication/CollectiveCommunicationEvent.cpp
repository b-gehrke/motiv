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
#include "CollectiveCommunicationEvent.hpp"

#include <utility>

CollectiveCommunicationEvent::CollectiveCommunicationEvent(std::vector<Member *> members,
                                                           otf2::definition::location *location,
                                                           types::communicator *communicator,
                                                           otf2::collective_type operation, uint32_t root) :
    location(location), members(std::move(members)), communicator(communicator), operation(operation),
    root(root) {
    auto starting = std::min_element(this->members.begin(), this->members.end(), [](const Member* lhs, const Member* rhs) {return lhs->start < rhs->start;});
    auto ending = std::max_element(this->members.begin(), this->members.end(), [](const Member* lhs, const Member* rhs) {return lhs->end < rhs->end;});

    this->start = (*starting)->start;
    this->end = (*ending)->end;
}

otf2::definition::location * CollectiveCommunicationEvent::getLocation() const {
    return location;
}

otf2::chrono::duration CollectiveCommunicationEvent::getStartTime() const {
    return start;
}

otf2::chrono::duration CollectiveCommunicationEvent::getEndTime() const {
    return end;
}

types::communicator * CollectiveCommunicationEvent::getCommunicator() const {
    return communicator;
}

CommunicationKind CollectiveCommunicationEvent::getKind() const {
    return Collective;
}

otf2::collective_type CollectiveCommunicationEvent::getOperation() const {
    return operation;
}

uint32_t CollectiveCommunicationEvent::getRoot() const {
    return root;
}

const std::vector<CollectiveCommunicationEvent::Member *> &CollectiveCommunicationEvent::getMembers() const {
    return members;
}

