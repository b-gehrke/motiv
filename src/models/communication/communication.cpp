#include "./communication.hpp"
#include "communicationkind.hpp"
#include "communicationevent.hpp"
#include "blockingp2pcommunicationevent.hpp"

Communication::Communication(const std::shared_ptr<CommunicationEvent>& start, const std::shared_ptr<CommunicationEvent>& end) : start(), end() {
}

std::shared_ptr<CommunicationEvent> Communication::getStart() const {
    return start;
}

std::shared_ptr<CommunicationEvent> Communication::getEnd() const {
    return end;
}
