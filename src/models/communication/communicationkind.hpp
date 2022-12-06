#ifndef MOTIV_COMMUNICATIONKIND_HPP
#define MOTIV_COMMUNICATIONKIND_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "src/types.h"
#include "src/models/builder.hpp"

/**
 * All different kinds of communication events.
 */
enum CommunicationKind {
    /**
     * The communication event was a blocking send operation (e.g. MPI_SSEND)
     */
    BlockingSend,

    /**
     * The communication event was a blocking receive operation (e.g. MPI_SRECEIVE)
     */
    BlockingReceive,

    /**
     * The communication event was a non blocking send operation (e.g. MPI_ISEND)
     */
    NonBlockingSend,

    /**
     * The communication event was a non blocking receive operation (e.g. MPI_IRECEIVE)
     */
    NonBlockingReceive,

    /**
     * The communication event was a collective operation (e.g. MPI_REDUCE)
     */
    Collective,

    /**
     * The communication event was a cancellation event (e.g. MPI_REQUEST_CANCEL)
     */
    RequestCancelled
};
#endif //MOTIV_COMMUNICATIONKIND_HPP
