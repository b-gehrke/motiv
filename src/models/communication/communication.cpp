#include "./communication.hpp"
#include "communicationkind.hpp"
#include "communicationevent.hpp"
#include "blockingp2pcommunicationevent.hpp"

Communication::Communication(CommunicationEvent &start, CommunicationEvent &anEnd) : start(start), end(anEnd) {}

CommunicationEvent &Communication::getStart() const {
    return start;
}

CommunicationEvent &Communication::getAnEnd() const {
    return end;
}
