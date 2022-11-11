#ifndef MOTIV_NONBLOCKINGRECEIVEEVENT_HPP
#define MOTIV_NONBLOCKINGRECEIVEEVENT_HPP


#include "nonblockingp2pcommunicationevent.hpp"

class NonBlockingReceiveEvent : public NonBlockingP2PCommunicationEvent {
public:
    NonBlockingReceiveEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                            const otf2::definition::location &location, const types::communicator &communicator);

    CommunicationKind getKind() override;
};


#endif //MOTIV_NONBLOCKINGRECEIVEEVENT_HPP
