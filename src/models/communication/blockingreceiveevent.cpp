#include "blockingreceiveevent.hpp"

CommunicationKind BlockingReceiveEvent::getKind() {
    return BlockingReceive;
}

BlockingReceiveEvent::BlockingReceiveEvent(const otf2::chrono::duration &timepoint,
                                           const otf2::definition::location &location,
                                           const types::communicator &communicator) : BlockingP2PCommunicationEvent(
    timepoint, location, communicator) {}
