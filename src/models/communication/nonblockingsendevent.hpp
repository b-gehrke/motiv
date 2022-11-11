#ifndef MOTIV_NONBLOCKINGSENDEVENT_HPP
#define MOTIV_NONBLOCKINGSENDEVENT_HPP


#include "nonblockingp2pcommunicationevent.hpp"

class NonBlockingSendEvent : public NonBlockingP2PCommunicationEvent {
public:
    NonBlockingSendEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                         const otf2::definition::location &location, const types::communicator &communicator);

    CommunicationKind getKind() override;
};


#endif //MOTIV_NONBLOCKINGSENDEVENT_HPP
