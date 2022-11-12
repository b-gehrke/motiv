#ifndef MOTIV_NONBLOCKINGP2PCOMMUNICATIONEVENT_HPP
#define MOTIV_NONBLOCKINGP2PCOMMUNICATIONEVENT_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "communicationevent.hpp"
#include "communicationkind.hpp"
#include "src/types.h"
#include "src/models/builder.hpp"

class NonBlockingP2PCommunicationEvent : public CommunicationEvent {
protected:
    NonBlockingP2PCommunicationEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                                     const otf2::definition::location &location, const types::communicator &communicator);

    otf2::chrono::duration start;
    otf2::chrono::duration end;
    otf2::definition::location location;
    types::communicator communicator;
public:
    otf2::definition::location getLocation() override;
    otf2::chrono::duration getStart() override;
    otf2::chrono::duration getEnd() override;
    types::communicator getCommunicator() override;
};

#endif //MOTIV_NONBLOCKINGP2PCOMMUNICATIONEVENT_HPP
