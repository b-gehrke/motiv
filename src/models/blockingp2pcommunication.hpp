#ifndef MOTIV_BLOCKINGP2PCOMMUNICATION_HPP
#define MOTIV_BLOCKINGP2PCOMMUNICATION_HPP

#include "p2pcommunication.hpp"
#include "../types.h"
#include "builder.hpp"
#include <otf2xx/otf2.hpp>
#include "./communication.hpp"
#include <utility>

class BlockingP2PCommunication : public P2PCommunication {
public:
    BlockingP2PCommunication(const otf2::definition::location &sender, const otf2::definition::location &receiver,
                             uint32_t msgTag, uint64_t msgLength,
                             const types::communicator &communicator,
                             const otf2::chrono::duration &sendTime, const otf2::chrono::duration &receiveTime);

    otf2::chrono::duration sendTime;
    otf2::chrono::duration receiveTime;

    BUILDER(BlockingP2PCommunication,
            BUILDER_FIELD(otf2::definition::location, sender)
                BUILDER_FIELD(otf2::definition::location, receiver)
                BUILDER_FIELD(uint32_t, msgTag)
                BUILDER_FIELD(uint64_t, msgLength)
                BUILDER_FIELD(types::communicator, communicator)
                BUILDER_FIELD(otf2::chrono::duration, sendTime)
                BUILDER_FIELD(otf2::chrono::duration, receiveTime),
            sender, receiver, msgTag, msgLength, communicator, sendTime, receiveTime)
};

#endif //MOTIV_BLOCKINGP2PCOMMUNICATION_HPP
