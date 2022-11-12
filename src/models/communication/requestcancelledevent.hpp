#ifndef MOTIV_REQUESTCANCELLEDEVENT_HPP
#define MOTIV_REQUESTCANCELLEDEVENT_HPP


#include "nonblockingp2pcommunicationevent.hpp"

class RequestCancelledEvent : public NonBlockingP2PCommunicationEvent {
public:
    RequestCancelledEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                          const otf2::definition::location &location, const types::communicator &communicator);

    CommunicationKind getKind() override;
};


#endif //MOTIV_REQUESTCANCELLEDEVENT_HPP
