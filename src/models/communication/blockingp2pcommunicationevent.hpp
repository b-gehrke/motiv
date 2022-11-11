#ifndef MOTIV_BLOCKINGP2PCOMMUNICATIONEVENT_HPP
#define MOTIV_BLOCKINGP2PCOMMUNICATIONEVENT_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "src/types.h"
#include "src/models/builder.hpp"
#include "communicationevent.hpp"
#include "communicationkind.hpp"
#include "./communication.hpp"

const otf2::chrono::duration BLOCKING_EVENT_DURATION(1);

class BlockingP2PCommunicationEvent : public CommunicationEvent {
protected:
public:
    BlockingP2PCommunicationEvent(const otf2::chrono::duration &timepoint, const otf2::definition::location &location,
                                  const types::communicator &communicator);

protected:

    otf2::chrono::duration timepoint;
    otf2::definition::location location;
    types::communicator communicator;
public:
    otf2::definition::location getLocation() override;
    otf2::chrono::duration getStart() override;
    otf2::chrono::duration getEnd() override;
    types::communicator getCommunicator() override;
};

#endif //MOTIV_BLOCKINGP2PCOMMUNICATIONEVENT_HPP
