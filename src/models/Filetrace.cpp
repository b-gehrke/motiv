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
#include "Filetrace.hpp"
#include "Range.hpp"
#include "src/utils.hpp"

FileTrace::FileTrace(std::vector<Slot *> &slotss,
                     std::vector<Communication *> &communications,
                     std::vector<CollectiveCommunicationEvent *> &collectiveCommunications_,
                     otf2::chrono::duration runtime) :
    slotsVec_(slotss),
    communications_(communications),
    collectiveCommunications_(collectiveCommunications_) {
    runtime_ = runtime;
    startTime_ = otf2::chrono::duration(0);

    slots_ = groupBy<Slot *, otf2::definition::location_group *, LocationGroupCmp>(
        Range(slotsVec_),
        [](const Slot *s) {
            return new otf2::definition::location_group(s->location->location_group());
        },
        [](const Slot *l, const Slot *r) {
            auto groupL = l->location->location_group();
            auto groupR = r->location->location_group();

            if (groupL.ref() == groupR.ref()) {
                return l->startTime < r->startTime;
            }

            return groupL.ref() < groupR.ref();
        });
}

std::map<otf2::definition::location_group *, Range<Slot *>, LocationGroupCmp> FileTrace::getSlots() const {
    return slots_;
}

Range<Communication *> FileTrace::getCommunications() {
    return Range(communications_);
}

Range<CollectiveCommunicationEvent *> FileTrace::getCollectiveCommunications() {
    return Range(collectiveCommunications_);
}

FileTrace::~FileTrace() {
    for (const auto &communication: this->collectiveCommunications_) {
        delete communication;
    }

    for (const auto &communication: this->communications_) {
        delete communication;
    }

    for (const auto &locationGroupSlotPair: this->slots_) {
        delete locationGroupSlotPair.first;

        for (const auto &slot: locationGroupSlotPair.second) {
            delete slot;
        }
    }
}
