#ifndef MOTIV_COMMUNICATION_HPP
#define MOTIV_COMMUNICATION_HPP

#include "src/models/builder.hpp"
#include "src/types.h"
#include "communicationkind.hpp"
#include "communicationevent.hpp"

#include "lib/otf2xx/include/otf2xx/otf2.hpp"

class Communication {
public:
    Communication(CommunicationEvent &start, CommunicationEvent &anEnd);

    [[nodiscard]] CommunicationEvent &getStart() const;
    [[nodiscard]] CommunicationEvent &getAnEnd() const;

private:
    CommunicationEvent& start;
    CommunicationEvent& end;
};

#endif //MOTIV_COMMUNICATION_HPP
