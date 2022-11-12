#ifndef MOTIV_BLOCKINGSENDEVENT_HPP
#define MOTIV_BLOCKINGSENDEVENT_HPP


#include "blockingp2pcommunicationevent.hpp"


/**
 * Class representing the blocking send event.
 */
class BlockingSendEvent : public BlockingP2PCommunicationEvent {
public:

    /**
     * Creates a new instance of the BlockingReceiveEvent class.
     *
     * @param timepoint Timepoint of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    BlockingSendEvent(const otf2::chrono::duration &timepoint, const otf2::definition::location &location,
                      const types::communicator &communicator);
    CommunicationKind getKind() override;
};


#endif //MOTIV_BLOCKINGSENDEVENT_HPP
