#include "./communication.hpp"
#include "communicationkind.hpp"
#include "communicationevent.hpp"
#include "blockingp2pcommunicationevent.hpp"

Communication::Communication(const CommunicationEvent *start, const CommunicationEvent *end) : start(start), end(end) {
}

const CommunicationEvent * Communication::getStart() const {
    return start;
}

const CommunicationEvent * Communication::getEnd() const {
    return end;
}
