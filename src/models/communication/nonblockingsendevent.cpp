#include "nonblockingsendevent.hpp"

NonBlockingSendEvent::NonBlockingSendEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                                           const otf2::definition::location &location,
                                           const types::communicator &communicator) : NonBlockingP2PCommunicationEvent(
    start, anEnd, location, communicator) {}

CommunicationKind NonBlockingSendEvent::getKind() {
    return NonBlockingSend;
}
