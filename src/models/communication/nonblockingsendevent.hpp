#ifndef MOTIV_NONBLOCKINGSENDEVENT_HPP
#define MOTIV_NONBLOCKINGSENDEVENT_HPP


#include "nonblockingp2pcommunicationevent.hpp"

class NonBlockingSendEvent : public NonBlockingP2PCommunicationEvent {
public:
    NonBlockingSendEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                         const otf2::definition::location &location, const types::communicator &communicator);

    CommunicationKind getKind() override;


    BUILDER(NonBlockingSendEvent,
            BUILDER_FIELD(otf2::chrono::duration, start)
            BUILDER_FIELD(otf2::chrono::duration, end)
            BUILDER_FIELD(otf2::definition::location, location)
            BUILDER_FIELD(types::communicator, communicator)
            BUILDER_OPTIONAL_FIELD(uint32_t, receiver),
            start, end, location, communicator)
};


#endif //MOTIV_NONBLOCKINGSENDEVENT_HPP
