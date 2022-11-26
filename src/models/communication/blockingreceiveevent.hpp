#ifndef MOTIV_BLOCKINGRECEIVEEVENT_HPP
#define MOTIV_BLOCKINGRECEIVEEVENT_HPP


#include "blockingp2pcommunicationevent.hpp"

/**
 * Class representing the blocking send event.
 */
class BlockingReceiveEvent : public BlockingP2PCommunicationEvent {
public:
    /**
     * Creates a new instance of the BlockingReceiveEvent class.
     *
     * @param timepoint Timepoint of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    BlockingReceiveEvent(const otf2::chrono::duration &timepoint, const otf2::definition::location &location,
                         const types::communicator &communicator);

    CommunicationKind getKind() const override;
};


#endif //MOTIV_BLOCKINGRECEIVEEVENT_HPP
