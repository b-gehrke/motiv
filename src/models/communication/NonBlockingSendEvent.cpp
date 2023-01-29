#include "NonBlockingSendEvent.hpp"

NonBlockingSendEvent::NonBlockingSendEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
                                           otf2::definition::location *location,
                                           types::communicator *communicator) : NonBlockingP2PCommunicationEvent(
    start, end, location, communicator) {}

CommunicationKind NonBlockingSendEvent::getKind() const {
    return NonBlockingSend;
}
