#ifndef MOTIV_COLLECTIVECOMMUNICATION_HPP
#define MOTIV_COLLECTIVECOMMUNICATION_HPP

#include <otf2xx/otf2.hpp>
#include "builder.hpp"
#include "../types.h"

class CollectiveCommunication {
public:
    struct Participation {
        const otf2::definition::location location;
        const otf2::chrono::duration startTime;
    };

    CollectiveCommunication(const otf2::chrono::duration &startTime, const otf2::chrono::duration &endTime,
                            const types::communicator &communicator, uint32_t root,
                            const std::vector<Participation> &participants);

    const otf2::chrono::duration startTime;
    const otf2::chrono::duration endTime;
    const types::communicator communicator;
    const uint32_t root;
    const std::vector<Participation> participants;

    BUILDER(CollectiveCommunication,
            BUILDER_FIELD(otf2::chrono::duration, startTime)
            BUILDER_FIELD(otf2::chrono::duration, endTime)
            BUILDER_FIELD(types::communicator, communicator)
            BUILDER_FIELD(uint32_t, root)
            BUILDER_FIELD(std::vector<Participation>, participants),
            startTime, endTime, communicator, root, participants)
};


#endif //MOTIV_COLLECTIVECOMMUNICATION_HPP
