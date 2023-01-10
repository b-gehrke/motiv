#include "requestcancelledevent.hpp"

RequestCancelledEvent::RequestCancelledEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
                                             otf2::definition::location *location,
                                             types::communicator *communicator)
    : NonBlockingP2PCommunicationEvent(start, end, location, communicator) {}

CommunicationKind RequestCancelledEvent::getKind() const {
    return RequestCancelled;
}
