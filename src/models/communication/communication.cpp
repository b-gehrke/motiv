#include "./communication.hpp"
#include "communicationkind.hpp"
#include "communicationevent.hpp"
#include "blockingp2pcommunicationevent.hpp"

Communication::Communication(const CommunicationEvent *start, const CommunicationEvent *end) : start(), end() {
}

CommunicationEvent * Communication::getStart() const {
    return start;
}

CommunicationEvent * Communication::getEnd() const {
    return end;
}
