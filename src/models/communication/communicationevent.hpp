#ifndef MOTIV_COMMUNICATIONEVENT_HPP
#define MOTIV_COMMUNICATIONEVENT_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "communicationkind.hpp"
#include "src/types.h"
#include "src/models/builder.hpp"

/**
 * Abstract class for generic Communication events. All communications handled by this application have a start and an
 * end event. See `Communication` for more details.
 */
class CommunicationEvent {
public:
    /**
     * Gets the location of the recorded event.
     * @return Location of the recorded event
     */
    virtual otf2::definition::location getLocation() = 0;

    /**
     * Gets the start time of the recorded event. The time is relative to the star time of the program.
     * @return Start time of the recorded event
     */
    virtual otf2::chrono::duration getStart() = 0;

    /**
     * Gets the end time of the recorded even. The time is relative to the star time of the program.
     * @return End time of the recorded event
     */
    virtual otf2::chrono::duration getEnd() = 0;

    /**
     * Gets the communicator the recorded event took place in.
     * @return Communicator of the event
     */
    virtual types::communicator getCommunicator() = 0;

    /**
     * Gets the kind of communication event. Implemented by each derived class.
     * @return Kind of event.
     */
    virtual CommunicationKind getKind() = 0;
};

#endif //MOTIV_COMMUNICATIONEVENT_HPP
