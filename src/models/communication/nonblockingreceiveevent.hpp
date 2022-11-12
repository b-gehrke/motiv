#ifndef MOTIV_NONBLOCKINGRECEIVEEVENT_HPP
#define MOTIV_NONBLOCKINGRECEIVEEVENT_HPP


#include "nonblockingp2pcommunicationevent.hpp"

class NonBlockingReceiveEvent : public NonBlockingP2PCommunicationEvent {
public:
    NonBlockingReceiveEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                            const otf2::definition::location &location, const types::communicator &communicator);

    CommunicationKind getKind() override;

    BUILDER(NonBlockingReceiveEvent,
            BUILDER_FIELD(otf2::chrono::duration, start)
            BUILDER_FIELD(otf2::chrono::duration, end)
            BUILDER_FIELD(otf2::definition::location, location)
            BUILDER_FIELD(types::communicator, communicator)
            BUILDER_OPTIONAL_FIELD(uint32_t, receiver),
            start, end, location, communicator)
};


#endif //MOTIV_NONBLOCKINGRECEIVEEVENT_HPP
