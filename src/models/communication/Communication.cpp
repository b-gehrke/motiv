#include "./Communication.hpp"
#include "CommunicationKind.hpp"
#include "CommunicationEvent.hpp"
#include "BlockingP2PCommunicationEvent.hpp"

Communication::Communication(const CommunicationEvent *start, const CommunicationEvent *end) : start(start), end(end) {
}

const CommunicationEvent * Communication::getStart() const {
    return start;
}

const CommunicationEvent * Communication::getEnd() const {
    return end;
}
