#ifndef MOTIV_COMMUNICATION_HPP
#define MOTIV_COMMUNICATION_HPP

#include "src/models/builder.hpp"
#include "src/types.h"
#include "communicationkind.hpp"
#include "communicationevent.hpp"

#include "lib/otf2xx/include/otf2xx/otf2.hpp"

class Communication {
public:
    Communication(const std::shared_ptr<CommunicationEvent> &start, const std::shared_ptr<CommunicationEvent> &end);

    [[nodiscard]] std::shared_ptr<CommunicationEvent> getStart() const;
    [[nodiscard]] std::shared_ptr<CommunicationEvent> getEnd() const;

private:
    std::shared_ptr<CommunicationEvent> start;
    std::shared_ptr<CommunicationEvent> end;
};

#endif //MOTIV_COMMUNICATION_HPP
