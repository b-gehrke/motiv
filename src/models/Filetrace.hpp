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
#ifndef MOTIV_FILETRACE_HPP
#define MOTIV_FILETRACE_HPP

#include "SubTrace.hpp"
#include "Range.hpp"

/**
 * @brief Trace representing the whole trace loaded from trace files
 */
class FileTrace : public SubTrace {
private:
    std::vector<Slot *> slotsVec_;
    std::vector<Communication*> communications_;
    std::vector<CollectiveCommunicationEvent*> collectiveCommunications_;
public:
    /**
     * Creates a new instance
     *
     * @param slotss vector of all slots from the trace file
     * @param communications vector of communications from the trace file
     * @param collectiveCommunications vector of collective communications from the trace file
     * @param runtime total runtime of the trace
     */
    FileTrace(std::vector<Slot*> &slotss,
              std::vector<Communication*> &communications,
              std::vector<CollectiveCommunicationEvent*> &collectiveCommunications,
              otf2::chrono::duration runtime);

    virtual ~FileTrace();

    /**
     * @copydoc Trace::getSlots()
     */
    [[nodiscard]] std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> getSlots() const override;

    /**
     * @copydoc Trace::getCommunications()
     */
    [[nodiscard]] Range<Communication*> getCommunications() override;

    /**
     * @copydoc Trace::getCollectiveCommunications()
     */
    [[nodiscard]] Range<CollectiveCommunicationEvent*> getCollectiveCommunications() override;

};

#endif //MOTIV_FILETRACE_HPP
