#include <utility>

#include "./blockingp2pcommunicationevent.hpp"

BlockingP2PCommunicationEvent::BlockingP2PCommunicationEvent(const otf2::chrono::duration &timepoint,
                                                             otf2::definition::location location,
                                                             types::communicator communicator) : timepoint(
    timepoint), location(std::move(location)), communicator(std::move(communicator)) {}

otf2::chrono::duration BlockingP2PCommunicationEvent::getStart() const {
    return timepoint;
}

otf2::definition::location BlockingP2PCommunicationEvent::getLocation() const {
    return location;
}

otf2::chrono::duration BlockingP2PCommunicationEvent::getEnd() const {
    return timepoint + BLOCKING_EVENT_DURATION;
}

types::communicator BlockingP2PCommunicationEvent::getCommunicator() const {
    return communicator;
}



