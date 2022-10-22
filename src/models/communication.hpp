//
// Created by bjoern on 20.10.22.
//

#ifndef MOTIV_COMMUNICATION_HPP
#define MOTIV_COMMUNICATION_HPP

#include <otf2xx/otf2.hpp>
#include "builder.hpp"

class Communication {
public:
    Communication(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                  const otf2::definition::location &sender, const otf2::definition::location &receiver,
                  uint32_t receiverRank);

    otf2::chrono::duration start;
    otf2::chrono::duration end;
    otf2::definition::location sender;
    otf2::definition::location receiver;
    uint32_t receiverRank;

    BUILDER(Communication,
            BUILDER_FIELD(otf2::chrono::duration, start)
            BUILDER_FIELD(otf2::chrono::duration, end)
            BUILDER_FIELD(otf2::definition::location, sender)
            BUILDER_FIELD(otf2::definition::location, receiver)
            BUILDER_FIELD(uint32_t, receiverRank),
            start, end, sender, receiver, receiverRank)
};

#endif //MOTIV_COMMUNICATION_HPP
