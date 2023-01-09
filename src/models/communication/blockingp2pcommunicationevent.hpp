#ifndef MOTIV_BLOCKINGP2PCOMMUNICATIONEVENT_HPP
#define MOTIV_BLOCKINGP2PCOMMUNICATIONEVENT_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "src/types.h"
#include "src/models/builder.hpp"
#include "communicationevent.hpp"
#include "communicationkind.hpp"
#include "./communication.hpp"

/**
 * Defines the duration of blocking communication events.
 *
 * A blocking communication event has only a single time point and therefore no duration. For easier use in the rest
 * of the application each blocking event is assigned a small duration nevertheless.
 */
const otf2::chrono::duration BLOCKING_EVENT_DURATION(1);


/**
 * Class representing blocking events in point to point communications like MPI_SSEND, MPI_SRECEIVE.
 *
 * This class bundles common functionality for these types of events and should be used as a base class and not
 * instantiated directly.
 */
class BlockingP2PCommunicationEvent : public CommunicationEvent {
protected:
    /**
     * Creates a new instance of the abstract BlockingP2PCommunicationEvent class.
     *
     * @param timepoint Timepoint of the event
     * @param location Location of the event
     * @param communicator Communicator the event took place in
     */
    BlockingP2PCommunicationEvent(const otf2::chrono::duration &timepoint, otf2::definition::location* location,
                                  types::communicator* communicator);

protected:
    otf2::chrono::duration timepoint;
    otf2::definition::location* location;
    types::communicator* communicator;
public:
    otf2::definition::location * getLocation() const override;
    otf2::chrono::duration getStart() const override;
    otf2::chrono::duration getEnd() const override;
    types::communicator * getCommunicator() const override;
};

#endif //MOTIV_BLOCKINGP2PCOMMUNICATIONEVENT_HPP
