#ifndef MOTIV_BLOCKINGSENDEVENT_HPP
#define MOTIV_BLOCKINGSENDEVENT_HPP


#include "BlockingP2PCommunicationEvent.hpp"


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
    BlockingSendEvent(const otf2::chrono::duration &timepoint, otf2::definition::location *location,
                      types::communicator *communicator);
    CommunicationKind getKind() const override;
};


#endif //MOTIV_BLOCKINGSENDEVENT_HPP
