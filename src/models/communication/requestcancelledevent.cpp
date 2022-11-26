#include "requestcancelledevent.hpp"

RequestCancelledEvent::RequestCancelledEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
                                             const otf2::definition::location &location,
                                             const types::communicator &communicator)
    : NonBlockingP2PCommunicationEvent(start, end, location, communicator) {}

CommunicationKind RequestCancelledEvent::getKind() const {
    return RequestCancelled;
}
