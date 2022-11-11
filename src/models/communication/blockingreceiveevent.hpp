#ifndef MOTIV_BLOCKINGRECEIVEEVENT_HPP
#define MOTIV_BLOCKINGRECEIVEEVENT_HPP


#include "blockingp2pcommunicationevent.hpp"

class BlockingReceiveEvent : public BlockingP2PCommunicationEvent {
public:
    BlockingReceiveEvent(const otf2::chrono::duration &timepoint, const otf2::definition::location &location,
                         const types::communicator &communicator);

    CommunicationKind getKind() override;
};


#endif //MOTIV_BLOCKINGRECEIVEEVENT_HPP
