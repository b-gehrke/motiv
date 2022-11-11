#ifndef MOTIV_BLOCKINGSENDEVENT_HPP
#define MOTIV_BLOCKINGSENDEVENT_HPP


#include "blockingp2pcommunicationevent.hpp"

class BlockingSendEvent : public BlockingP2PCommunicationEvent {
public:
    BlockingSendEvent(const otf2::chrono::duration &timepoint, const otf2::definition::location &location,
                      const types::communicator &communicator);
    CommunicationKind getKind() override;
};


#endif //MOTIV_BLOCKINGSENDEVENT_HPP
