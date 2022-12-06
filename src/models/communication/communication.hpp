#ifndef MOTIV_COMMUNICATION_HPP
#define MOTIV_COMMUNICATION_HPP

#include "src/models/builder.hpp"
#include "src/types.h"
#include "communicationkind.hpp"
#include "communicationevent.hpp"

#include "lib/otf2xx/include/otf2xx/otf2.hpp"

/**
 * Class representing any (successful or unsuccessful) communication.
 *
 * Each communication consists of two events: An event starting the communication and one ending it. A communication
 * does not have to successful. For example the end event might be of kind `RequestCancelled` indicating a request was not
 * completed.
 */
class Communication {
public:
    /**
     * Creates a new instance of the `Communication` class
     * @param start The event initiating the communication
     * @param end The event ending the communication
     */
    Communication(const std::shared_ptr<CommunicationEvent> &start, const std::shared_ptr<CommunicationEvent> &end);

    /**
     * Gets the event that initiated the communication.
     * @return Event that initiated the communication
     */
    [[nodiscard]] std::shared_ptr<CommunicationEvent> getStart() const;

    /**
     * Gets the event that ended the communication
     * @return event that ended the communication
     */
    [[nodiscard]] std::shared_ptr<CommunicationEvent> getEnd() const;

private:
    std::shared_ptr<CommunicationEvent> start;
    std::shared_ptr<CommunicationEvent> end;
};

#endif //MOTIV_COMMUNICATION_HPP
