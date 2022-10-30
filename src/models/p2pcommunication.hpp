#ifndef MOTIV_P2PCOMMUNICATION_HPP
#define MOTIV_P2PCOMMUNICATION_HPP

#include "../types.h"
#include "builder.hpp"
#include <otf2xx/otf2.hpp>
#include "./communication.hpp"
#include <utility>

/**
 * # MPI Communication / Events with data
 * Blocking
 * - send start time
 * - receive start time
 * - sender
 * - receiver
 * - msg tag
 * - msg length
 * - msg type
 * - communicator
 *
 * Non-blocking
 * - send start time
 * - send end time
 * - receive start time
 * - receive end time
 * - sender
 * - receiver
 * - msg tag
 * - msg length
 * - msg type
 * - communicator
 * - request id
 *
 * RequestTest (probing, but request not completed yet)
 * - test time
 * - test location
 * - request id
 *
 * RequestCancelled
 * - cancel time
 * - cancel location
 * - request id
 *
 * Collective
 * - location
 * - start time(s)
 * - end time
 * - kind of collective operation
 * - communicator
 * - root location
 *
 * # Datastructures
 *
 * P2PCommunication { sender, receiver, msgTag, msgType, msgLength, communicator }
 * BlockingP2PCommunication { sendTime, receiveTime } -> P2PCommunication
 * NonBlockingP2PCommunication { sendStartTime, sendEndTime, receiveStartTime, receiveEndTime, requestId, state = COMPLETED | CANCELLED }
 *
 * RequestTested { time, location, requestId }
 *
 * Collective { startTime, endTime, participants [{ location, startTime }], communicator, root }
 *
 */

class P2PCommunication {
protected:
    P2PCommunication(otf2::definition::location sender, otf2::definition::location receiver,
                     uint32_t msgTag, uint64_t msgLength,
                     const types::communicator &communicator);

public:
    otf2::definition::location sender;
    otf2::definition::location receiver;
    uint32_t msgTag;
    uint64_t msgLength;
    types::communicator communicator;
};
#endif //MOTIV_P2PCOMMUNICATION_HPP
