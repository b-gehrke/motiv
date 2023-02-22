
#include <chrono>
#include "otf2xx/definition/location.hpp"
#include "NonBlockingP2PCommunicationEvent.hpp"

NonBlockingP2PCommunicationEvent::NonBlockingP2PCommunicationEvent(const otf2::chrono::duration &start,
                                                                   const otf2::chrono::duration &end,
                                                                   otf2::definition::location *location,
                                                                   types::communicator *communicator)
        : start(start), end(end), location(location), communicator(communicator) {}

otf2::definition::location * NonBlockingP2PCommunicationEvent::getLocation() const {
    return location;
}

otf2::chrono::duration NonBlockingP2PCommunicationEvent::getStartTime() const {
    return start;
}

otf2::chrono::duration NonBlockingP2PCommunicationEvent::getEndTime() const {
    return end;
}

types::communicator * NonBlockingP2PCommunicationEvent::getCommunicator() const {
    return communicator;
}
