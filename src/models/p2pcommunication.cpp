#include "p2pcommunication.hpp"

P2PCommunication::P2PCommunication(otf2::definition::location sender, otf2::definition::location receiver,
                                   const uint32_t msgTag, const uint64_t msgLength,
                                   const types::communicator &communicator) :
    sender(std::move(sender)), receiver(std::move(receiver)), msgTag(msgTag), msgLength(msgLength),
    communicator(communicator) {

}

