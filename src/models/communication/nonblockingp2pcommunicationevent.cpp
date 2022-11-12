
#include <chrono>
#include "otf2xx/definition/location.hpp"
#include "nonblockingp2pcommunicationevent.hpp"

NonBlockingP2PCommunicationEvent::NonBlockingP2PCommunicationEvent(const std::chrono::duration<long, std::ratio<1, 1000000000>> &start,
                                                                   const std::chrono::duration<long, std::ratio<1, 1000000000>> &anEnd,
                                                                   const otf2::definition::location &location,
                                                                   const std::variant <otf2::definition::comm, otf2::definition::inter_comm> &communicator)
    : start(start), end(anEnd), location(location), communicator(communicator) {}

otf2::definition::location NonBlockingP2PCommunicationEvent::getLocation() {
    return location;
}

otf2::chrono::duration NonBlockingP2PCommunicationEvent::getStart() {
    return start;
}

otf2::chrono::duration NonBlockingP2PCommunicationEvent::getEnd() {
    return end;
}

types::communicator NonBlockingP2PCommunicationEvent::getCommunicator() {
    return communicator;
}
