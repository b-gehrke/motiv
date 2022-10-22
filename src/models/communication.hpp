#ifndef MOTIV_COMMUNICATION_HPP
#define MOTIV_COMMUNICATION_HPP

#include <otf2xx/otf2.hpp>
#include "builder.hpp"

class Communication {
public:
    /**
     * Creates a new instance.
     *
     * @param start Start time of the communication (relative to the start of of the program)
     * @param end End time of the communication (relative to the start of of the program)
     * @param sender Location information of the sender
     * @param receiver Location information of the receiver
     * @param receiverRank MPI rank of the receiver
     */
    Communication(const otf2::chrono::duration &start,
                  const otf2::chrono::duration &end,
                  otf2::definition::location sender,
                  otf2::definition::location receiver,
                  uint32_t receiverRank);

    /**
     * Start time of the communication (relative to the start of of the program)
     */
    otf2::chrono::duration start;

    /**
     * End time of the communication (relative to the start of of the program)
     */
    otf2::chrono::duration end;

    /**
     * Location information of the sender
     */
    otf2::definition::location sender;
    /**
     * Location information of the receiver
     */
    otf2::definition::location receiver;
    /**
     * MPI rank of the receiver
     */
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
