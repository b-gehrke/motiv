#include "BlockingSendEvent.hpp"

BlockingSendEvent::BlockingSendEvent(const otf2::chrono::duration &timepoint,
                                     otf2::definition::location *location,
                                     types::communicator *communicator) : BlockingP2PCommunicationEvent(timepoint,
                                                                                                        location,
                                                                                                        communicator) {}

CommunicationKind BlockingSendEvent::getKind() const {
    return BlockingSend;
}
