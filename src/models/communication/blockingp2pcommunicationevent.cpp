#include "./blockingp2pcommunicationevent.hpp"

BlockingP2PCommunicationEvent::BlockingP2PCommunicationEvent(const otf2::chrono::duration &timepoint,
                                                             const otf2::definition::location &location,
                                                             const types::communicator &communicator) : timepoint(
    timepoint), location(location), communicator(communicator) {}

otf2::chrono::duration BlockingP2PCommunicationEvent::getStart() {
    return timepoint;
}

otf2::definition::location BlockingP2PCommunicationEvent::getLocation() {
    return location;
}

otf2::chrono::duration BlockingP2PCommunicationEvent::getEnd() {
    return timepoint + BLOCKING_EVENT_DURATION;
}

types::communicator BlockingP2PCommunicationEvent::getCommunicator() {
    return communicator;
}



