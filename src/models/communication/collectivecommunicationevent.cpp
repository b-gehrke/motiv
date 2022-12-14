#include "collectivecommunicationevent.hpp"

#include <utility>

CollectiveCommunicationEvent::CollectiveCommunicationEvent(std::vector<Member *> members,
                                                           otf2::definition::location *location,
                                                           types::communicator *communicator,
                                                           otf2::collective_type operation, uint32_t root) :
    members(std::move(members)), location(location), communicator(communicator), operation(operation),
    root(root), start(0), end(0) {
    auto starting = std::min_element(this->members.begin(), this->members.end(), [](const Member* lhs, const Member* rhs) {return lhs->start < rhs->start;});
    auto ending = std::max_element(this->members.begin(), this->members.end(), [](const Member* lhs, const Member* rhs) {return lhs->end < rhs->end;});

    this->start = (*starting)->start;
    this->end = (*ending)->end;
}

otf2::definition::location * CollectiveCommunicationEvent::getLocation() const {
    return location;
}

otf2::chrono::duration CollectiveCommunicationEvent::getStart() const {
    return start;
}

otf2::chrono::duration CollectiveCommunicationEvent::getEnd() const {
    return end;
}

types::communicator * CollectiveCommunicationEvent::getCommunicator() const {
    return communicator;
}

CommunicationKind CollectiveCommunicationEvent::getKind() const {
    return Collective;
}

otf2::collective_type CollectiveCommunicationEvent::getOperation() const {
    return operation;
}

uint32_t CollectiveCommunicationEvent::getRoot() const {
    return root;
}

