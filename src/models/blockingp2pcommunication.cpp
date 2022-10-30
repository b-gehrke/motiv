#include "blockingp2pcommunication.hpp"

BlockingP2PCommunication::BlockingP2PCommunication(const otf2::definition::location &sender,
                                                   const otf2::definition::location &receiver,
                                                   const uint32_t msgTag, const uint64_t msgLength,
                                                   const types::communicator &communicator,
                                                   const otf2::chrono::duration &sendTime,
                                                   const otf2::chrono::duration &receiveTime) :
    sendTime(sendTime),
    receiveTime(receiveTime),
    P2PCommunication(sender, receiver, msgTag, msgLength, communicator) {}
