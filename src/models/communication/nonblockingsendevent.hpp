#ifndef MOTIV_NONBLOCKINGSENDEVENT_HPP
#define MOTIV_NONBLOCKINGSENDEVENT_HPP


#include "nonblockingp2pcommunicationevent.hpp"

/**
 * Class representing the non blocking send event.
 */
class NonBlockingSendEvent : public NonBlockingP2PCommunicationEvent {
public:
    /**
     * Creates a new instance of the NonBlockingSendEvent class.
     *
     * @param start Start time of the event
     * @param end End time of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    NonBlockingSendEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
                         const otf2::definition::location &location, const types::communicator &communicator);

    CommunicationKind getKind() const override;


    BUILDER(NonBlockingSendEvent,
            BUILDER_FIELD(otf2::chrono::duration, start)
            BUILDER_FIELD(otf2::chrono::duration, end)
            BUILDER_FIELD(otf2::definition::location, location)
            BUILDER_FIELD(types::communicator, communicator)
            BUILDER_OPTIONAL_FIELD(uint32_t, receiver), // The receiver field is needed to match the receiving call. The
                                                        // location instance of the receiver is only known in the
                                                        // receive event.
            start, end, location, communicator)
};


#endif //MOTIV_NONBLOCKINGSENDEVENT_HPP
