#include "./Communication.hpp"
#include "CommunicationKind.hpp"
#include "CommunicationEvent.hpp"
#include "BlockingP2PCommunicationEvent.hpp"

Communication::Communication(const CommunicationEvent *start, const CommunicationEvent *end) : start(start), end(end) {
}

const CommunicationEvent * Communication::getStartEvent() const {
    return start;
}

const CommunicationEvent * Communication::getEndEvent() const {
    return end;
}

types::TraceTime Communication::getStartTime() const {
    return start->getStartTime();
}

types::TraceTime Communication::getEndTime() const {
    return end->getEndTime();
}
