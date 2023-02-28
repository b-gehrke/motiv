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

#ifndef MOTIV_COLLECTIVECOMMUNICATIONEVENT_HPP
#define MOTIV_COLLECTIVECOMMUNICATIONEVENT_HPP


#include "CommunicationEvent.hpp"

#include <utility>

/**
 * @brief A class representing an MPI collective operation
 *
 * This class represents an MPI collective operation. It contains all involved members (MPI ranks) and when they joined
 * and completed the operation.
 */
class CollectiveCommunicationEvent : public CommunicationEvent {
public:
    /**
     * @brief A class representing a member of a collective operation
     *
     * This class represents a member of an MPI collective operation.
     */
    class Member {
    public:
        /**
         * @brief Constructs a new instance of the Member class
         * @param start The time when the member did the collective operation call
         * @param anEnd The time when the member ended the collective operation call
         * @param location Location of the member
         */
        Member(const otf2::chrono::duration &start,
               const otf2::chrono::duration &anEnd,
               otf2::definition::location *location) :
               start(start), end(anEnd), location(location) {}

    public:
        const otf2::chrono::duration start; /**< The time when the member did the collective operation call */
        const otf2::chrono::duration end; /**< The time when the member ended the collective operation call*/
        const otf2::definition::location* location; /**< Location of the member*/

    public:
        /**
        * @brief Returns the start time of the communication
        *
        * @return The start time of the communication
        */
        [[nodiscard]] const otf2::chrono::duration &getStart() const {
            return start;
        }

        /**
         * @brief Returns the end time of the communication
         *
         * @return The end time of the communication
         */
        [[nodiscard]] const otf2::chrono::duration &getEnd() const {
            return end;
        }

        /**
         * @brief Returns the location of the member
         *
         * @return The location of the member
         */
        [[nodiscard]] const otf2::definition::location * getLocation() const {
            return location;
        }

        BUILDER(Member,
                BUILDER_FIELD(otf2::chrono::duration, start)
                BUILDER_FIELD(otf2::chrono::duration, end)
                BUILDER_FIELD(otf2::definition::location*, location),
                start, end, location)
    };

public:
    /**
     * @brief Creates a new instance of the CollectiveCommunicationEvent class
     *
     * @param members Vector of members participating in the collective operation
     * @param location The location of the longest waiting member
     * @param communicator The communicator of the collective operation
     * @param operation The kind of the collective operation
     * @param root The rank of the root of the operation. Can be any of otf2::common::collective_root_type
     */
    CollectiveCommunicationEvent(std::vector<Member *> members,
                                 otf2::definition::location *location,
                                 types::communicator *communicator,
                                 otf2::collective_type operation,
                                 uint32_t root);
    ~CollectiveCommunicationEvent() override = default;

    /**
     * @brief Returns the location of the longest waiting member
     * @return The location of the longest waiting member
     */
    [[nodiscard]] otf2::definition::location * getLocation() const override;

    /**
     * Returns the start time of the collective operations
     *
     * The start time of the collective operation is the time the first call to the collective operation was made. This
     * corresponds with the start time of the first member.
     *
     * @return The start time of the collective operation
     */
    [[nodiscard]] otf2::chrono::duration getStartTime() const override;

    /**
     * @brief Returns the end time of the collective operations.
     *
     * The end time of the collective operation is the time the last member
     * @return The end time of the collective operation
     */
    [[nodiscard]] otf2::chrono::duration getEndTime() const override;

    /**
     * @copydoc CommunicationEvent::getCommunicator()
     */
    [[nodiscard]] types::communicator * getCommunicator() const override;

    /**
     * @copybrief CommunicationEvent::getKind()
     * @return Returns CommunicationKind::Collective
     */
    [[nodiscard]] CommunicationKind getKind() const override;

    /**
     * @brief Returns the kind of the collective operation.
     * @return The kind of the collective operation.
     */
    [[nodiscard]] otf2::collective_type getOperation() const;

    /**
     * @brief Returns the root of the collective operation.
     *
     *
     * @return Can be any of otf2::common::collective_root_type
     */
    [[nodiscard]] uint32_t getRoot() const;

    /**
     * @brief Returns all members participating in the collective operation.
     * @return All members involved in the collective operation
     */
    [[nodiscard]] const std::vector<Member *> &getMembers() const;

    BUILDER(CollectiveCommunicationEvent,
            BUILDER_FIELD(std::vector<Member*>, members)
                BUILDER_FIELD(otf2::definition::location*, location)
                BUILDER_FIELD(types::communicator*, communicator)
                BUILDER_FIELD(otf2::collective_type, operation)
                BUILDER_FIELD(uint32_t, root),
            members, location, communicator, operation, root)

private:
    otf2::chrono::duration start{};
    otf2::chrono::duration end{};
    otf2::definition::location* location;
    std::vector<Member*> members;
    types::communicator* communicator;
    otf2::common::collective_type operation;
    std::uint32_t root;
};


#endif //MOTIV_COLLECTIVECOMMUNICATIONEVENT_HPP
