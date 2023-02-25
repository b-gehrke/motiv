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
#ifndef MOTIV_SUBTRACE_HPP
#define MOTIV_SUBTRACE_HPP

#include "Trace.hpp"
#include "Range.hpp"


/**
 * Trace representing a section of a larger trace.
 */
class SubTrace : public Trace {
public:
    /**
     * @copydoc Trace::getSlots()
     */
    [[nodiscard]] std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> getSlots() const override;

    /**
     * @copydoc Trace::getRuntime()
     */
    [[nodiscard]] otf2::chrono::duration getRuntime() const override;

    /**
     * @copydoc Trace::subtrace()
     */
    [[nodiscard]] Trace* subtrace(otf2::chrono::duration from, otf2::chrono::duration to) override;

    /**
     * @copydoc Trace::getCommunications()
     */
    [[nodiscard]] Range<Communication*> getCommunications() override;


    /**
     * @copydoc Trace::getCommunications()
     */
    [[nodiscard]] Range<CollectiveCommunicationEvent*> getCollectiveCommunications() override;


    /**
     * @copydoc Trace::getStartTime()
     */
    [[nodiscard]] otf2::chrono::duration getStartTime() const override;
    [[nodiscard]] types::TraceTime getEndTime() const override;
    [[nodiscard]] types::TraceTime getDuration() const override;

protected:
    /**
     * Backing field for the range of slots of this subtrace
     */
    std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> slots_;

    /**
     * Backing field for communications of this subtrace
     */
    Range<Communication*> communications_;

    /**
     * Backing field for collective communications of this subtrace
     */
    Range<CollectiveCommunicationEvent*> collectiveCommunications_;

    /**
     * Backing field for the runtime of this subtrace
     */
    otf2::chrono::duration runtime_{};

    /**
     * Backing field for the start time of this subtrace
     */
    otf2::chrono::duration startTime_{};
public:
    /**
     * Initializes an empty subtrace
     */
    SubTrace();

    /**
     * Initializes a new instance.
     *
     * @param slots Range of slots this subtrace covers
     * @param communications Range of communications this subtrace covers
     * @param runtime Runtime of this subtrace
     */
    SubTrace(std::map<otf2::definition::location_group*, Range<Slot*>, LocationGroupCmp> &slots,
             const Range<Communication*> &communications,
             const Range<CollectiveCommunicationEvent*> &collectiveCommunications,
             const otf2::chrono::duration &runtime,
             const otf2::chrono::duration &startTime);
};

#endif //MOTIV_SUBTRACE_HPP
