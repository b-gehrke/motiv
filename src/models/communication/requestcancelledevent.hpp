#ifndef MOTIV_REQUESTCANCELLEDEVENT_HPP
#define MOTIV_REQUESTCANCELLEDEVENT_HPP


#include "nonblockingp2pcommunicationevent.hpp"

/**
 * Class representing the request cancelled event.
 */
class RequestCancelledEvent : public NonBlockingP2PCommunicationEvent {
public:
    /**
     * Creates a new instance of the RequestCancelledEvent class.
     *
     * @param start Start time of the event
     * @param end End time of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    RequestCancelledEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
                          const otf2::definition::location &location, const types::communicator &communicator);

    CommunicationKind getKind() override;
};


#endif //MOTIV_REQUESTCANCELLEDEVENT_HPP
