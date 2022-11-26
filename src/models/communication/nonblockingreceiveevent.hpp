#ifndef MOTIV_NONBLOCKINGRECEIVEEVENT_HPP
#define MOTIV_NONBLOCKINGRECEIVEEVENT_HPP


#include "nonblockingp2pcommunicationevent.hpp"

/**
 * Class representing the non blocking receive event.
 */
class NonBlockingReceiveEvent : public NonBlockingP2PCommunicationEvent {
public:

    /**
     * Creates a new instance of the NonBlockingReceiveEvent class.
     *
     * @param start Start time of the event
     * @param end End time of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    NonBlockingReceiveEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                            const otf2::definition::location &location, const types::communicator &communicator);

    CommunicationKind getKind() const override;

    BUILDER(NonBlockingReceiveEvent,
            BUILDER_FIELD(otf2::chrono::duration, start)
            BUILDER_FIELD(otf2::chrono::duration, end)
            BUILDER_FIELD(otf2::definition::location, location)
            BUILDER_FIELD(types::communicator, communicator)
            BUILDER_OPTIONAL_FIELD(uint32_t, sender), // The sender field is needed to match the sending call. The
                                                      // location instance of the sender is only known in the
                                                      // send event.
            start, end, location, communicator)
};


#endif //MOTIV_NONBLOCKINGRECEIVEEVENT_HPP
