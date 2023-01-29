#include "BlockingReceivEevent.hpp"

CommunicationKind BlockingReceiveEvent::getKind() const {
    return BlockingReceive;
}

BlockingReceiveEvent::BlockingReceiveEvent(const otf2::chrono::duration &timepoint,
                                           otf2::definition::location *location,
                                           types::communicator *communicator) : BlockingP2PCommunicationEvent(
    timepoint, location, communicator) {}
