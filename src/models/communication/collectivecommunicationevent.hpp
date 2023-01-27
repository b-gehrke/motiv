
#ifndef MOTIV_COLLECTIVECOMMUNICATIONEVENT_HPP
#define MOTIV_COLLECTIVECOMMUNICATIONEVENT_HPP


#include "communicationevent.hpp"

#include <utility>

class CollectiveCommunicationEvent : public CommunicationEvent {
public:
    class Member {
    public:
        Member(const otf2::chrono::duration &start,
               const otf2::chrono::duration &anEnd,
               otf2::definition::location *location) :
               start(start), end(anEnd), location(location) {}

    public:
        const otf2::chrono::duration start;
        const otf2::chrono::duration end;
        const otf2::definition::location* location;

    public:
        [[nodiscard]] const otf2::chrono::duration &getStart() const {
            return start;
        }

        [[nodiscard]] const otf2::chrono::duration &getEnd() const {
            return end;
        }

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
    CollectiveCommunicationEvent(std::vector<Member *> members,
                                 otf2::definition::location *location,
                                 types::communicator *communicator,
                                 otf2::collective_type operation,
                                 uint32_t root);

    [[nodiscard]] otf2::definition::location * getLocation() const override;
    [[nodiscard]] otf2::chrono::duration getStart() const override;
    [[nodiscard]] otf2::chrono::duration getEnd() const override;
    [[nodiscard]] types::communicator * getCommunicator() const override;
    [[nodiscard]] CommunicationKind getKind() const override;
    [[nodiscard]] otf2::collective_type getOperation() const;
    [[nodiscard]] uint32_t getRoot() const;
    [[nodiscard]] const std::vector<Member *> &getMembers() const;

    BUILDER(CollectiveCommunicationEvent,
            BUILDER_FIELD(std::vector<Member*>, members)
                BUILDER_FIELD(otf2::definition::location*, location)
                BUILDER_FIELD(types::communicator*, communicator)
                BUILDER_FIELD(otf2::collective_type, operation)
                BUILDER_FIELD(uint32_t, root),
            members, location, communicator, operation, root)

private:
    otf2::chrono::duration start;
    otf2::chrono::duration end;
    otf2::definition::location* location;
    std::vector<Member*> members;
    types::communicator* communicator;
    otf2::common::collective_type operation;
    std::uint32_t root;
};


#endif //MOTIV_COLLECTIVECOMMUNICATIONEVENT_HPP
