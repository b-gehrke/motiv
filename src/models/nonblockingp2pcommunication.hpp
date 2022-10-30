#ifndef MOTIV_NONBLOCKINGP2PCOMMUNICATION_HPP
#define MOTIV_NONBLOCKINGP2PCOMMUNICATION_HPP

#include "p2pcommunication.hpp"
#include "../types.h"
#include "builder.hpp"
#include <otf2xx/otf2.hpp>
#include "blockingp2pcommunication.hpp"
#include "./communication.hpp"
#include <utility>

class NonBlockingP2PCommunication : public P2PCommunication {
public:
    enum Result {
        Cancelled,
        Completed
    };

    NonBlockingP2PCommunication(const otf2::definition::location &sender, const otf2::definition::location &receiver,
                                uint32_t msgTag, uint64_t msgLength,
                                const types::communicator &communicator,
                                const otf2::chrono::duration &sendStartTime,
                                const otf2::chrono::duration &sendEndTime,
                                const otf2::chrono::duration &receiveStartTime,
                                const otf2::chrono::duration &receiveEndTime,
                                const uint32_t &requestId,
                                const Result &result);

    const otf2::chrono::duration sendStartTime;
    const otf2::chrono::duration sendEndTime;
    const otf2::chrono::duration receiveStartTime;
    const otf2::chrono::duration receiveEndTime;
    const uint32_t requestId;
    const Result result;

    BUILDER(NonBlockingP2PCommunication,
            BUILDER_FIELD(otf2::definition::location, sender)
                BUILDER_FIELD(otf2::definition::location, receiver)
                BUILDER_FIELD(uint32_t, msgTag)
                BUILDER_FIELD(uint32_t, msgLength)
                BUILDER_FIELD(types::communicator, communicator)
                BUILDER_FIELD(otf2::chrono::duration, sendStartTime)
                BUILDER_FIELD(otf2::chrono::duration, sendEndTime)
                BUILDER_FIELD(otf2::chrono::duration, receiveStartTime)
                BUILDER_FIELD(otf2::chrono::duration, receiveEndTime)
                BUILDER_FIELD(uint32_t, requestId)
                BUILDER_FIELD(Result, result),
            sender, receiver, msgTag, msgLength, communicator, sendStartTime, sendEndTime, receiveStartTime, receiveEndTime, requestId, result)
};

#endif //MOTIV_NONBLOCKINGP2PCOMMUNICATION_HPP
