#include "nonblockingreceiveevent.hpp"

NonBlockingReceiveEvent::NonBlockingReceiveEvent(const otf2::chrono::duration &start,
                                                 const otf2::chrono::duration &anEnd,
                                                 otf2::definition::location *location,
                                                 types::communicator *communicator)
    : NonBlockingP2PCommunicationEvent(start, anEnd, location, communicator) {}

CommunicationKind NonBlockingReceiveEvent::getKind() const {
    return NonBlockingReceive;
}
