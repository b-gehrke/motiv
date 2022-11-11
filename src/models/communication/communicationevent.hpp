#ifndef MOTIV_COMMUNICATIONEVENT_HPP
#define MOTIV_COMMUNICATIONEVENT_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "communicationkind.hpp"
#include "src/types.h"
#include "src/models/builder.hpp"

class CommunicationEvent {
public:
    virtual otf2::definition::location getLocation() = 0;
    virtual otf2::chrono::duration getStart() = 0;
    virtual otf2::chrono::duration getEnd() = 0;
    virtual types::communicator getCommunicator() = 0;
    virtual CommunicationKind getKind() = 0;
};

#endif //MOTIV_COMMUNICATIONEVENT_HPP
