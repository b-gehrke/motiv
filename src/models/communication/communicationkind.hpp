#ifndef MOTIV_COMMUNICATIONKIND_HPP
#define MOTIV_COMMUNICATIONKIND_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "src/types.h"
#include "src/models/builder.hpp"

enum CommunicationKind {
    BlockingSend,
    BlockingReceive,
    NonBlockingSend,
    NonBlockingReceive,
    Collective
};
#endif //MOTIV_COMMUNICATIONKIND_HPP
