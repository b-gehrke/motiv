#include "blockingsendevent.hpp"

BlockingSendEvent::BlockingSendEvent(const otf2::chrono::duration &timepoint,
                                     const otf2::definition::location &location,
                                     const types::communicator &communicator) : BlockingP2PCommunicationEvent(timepoint,
                                                                                                              location,
                                                                                                              communicator) {}

CommunicationKind BlockingSendEvent::getKind() const {
    return BlockingSend;
}
