#include <utility>

#include "./BlockingP2PCommunicationEvent.hpp"

BlockingP2PCommunicationEvent::BlockingP2PCommunicationEvent(const otf2::chrono::duration &timepoint,
                                                             otf2::definition::location* location,
                                                             types::communicator* communicator) : timepoint(
    timepoint), location(location), communicator(communicator) {}

otf2::chrono::duration BlockingP2PCommunicationEvent::getStartTime() const {
    return timepoint;
}

otf2::definition::location * BlockingP2PCommunicationEvent::getLocation() const {
    return location;
}

otf2::chrono::duration BlockingP2PCommunicationEvent::getEndTime() const {
    return timepoint + BLOCKING_EVENT_DURATION;
}

types::communicator * BlockingP2PCommunicationEvent::getCommunicator() const {
    return communicator;
}



