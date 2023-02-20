#ifndef MOTIV_NONBLOCKINGP2PCOMMUNICATIONEVENT_HPP
#define MOTIV_NONBLOCKINGP2PCOMMUNICATIONEVENT_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "CommunicationEvent.hpp"
#include "CommunicationKind.hpp"
#include "src/types.h"
#include "src/models/Builder.hpp"

/**
 * Class representing non blocking events in point to point communications like MPI_ISEND, MPI_IRECEIVE.
 *
 * This class bundles common functionality for these types of events and should be used as a base class and not
 * instantiated directly.
 */
class NonBlockingP2PCommunicationEvent : public CommunicationEvent {
protected:
    /**
     * Creates a new instance of the abstract NonBlockingP2PCommunicationEvent class.
     *
     * @param start Start time of the event
     * @param end End time of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    NonBlockingP2PCommunicationEvent(const otf2::chrono::duration &start, const otf2::chrono::duration &end,
                                     otf2::definition::location* location, types::communicator* communicator);

    otf2::chrono::duration start;
    otf2::chrono::duration end;
    otf2::definition::location* location;
    types::communicator* communicator;
public:
    otf2::definition::location * getLocation() const override;
    otf2::chrono::duration getStartTime() const override;
    otf2::chrono::duration getEndTime() const override;
    types::communicator * getCommunicator() const override;
};

#endif //MOTIV_NONBLOCKINGP2PCOMMUNICATIONEVENT_HPP
