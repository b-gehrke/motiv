#include "nonblockingp2pcommunication.hpp"



NonBlockingP2PCommunication::NonBlockingP2PCommunication(const otf2::definition::location &sender,
                                                         const otf2::definition::location &receiver,
                                                         uint32_t msgTag,
                                                         uint64_t msgLength,
                                                         const types::communicator &communicator,
                                                         const otf2::chrono::duration &sendStartTime,
                                                         const otf2::chrono::duration &sendEndTime,
                                                         const otf2::chrono::duration &receiveStartTime,
                                                         const otf2::chrono::duration &receiveEndTime,
                                                         const uint32_t &requestId,
                                                         const NonBlockingP2PCommunication::Result &result) :
    sendStartTime(sendStartTime),
    sendEndTime(sendEndTime),
    receiveStartTime(receiveStartTime),
    receiveEndTime(receiveEndTime),
    requestId(requestId),
    result(result),
    P2PCommunication(sender, receiver, msgTag, msgLength, communicator) {

}
