/*
 * Marvelous OTF2 Traces Interactive Visualizer (MOTIV)
 * Copyright (C) 2023 Florian Gallrein, Björn Gehrke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MOTIV_COMMUNICATIONKIND_HPP
#define MOTIV_COMMUNICATIONKIND_HPP

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "src/types.hpp"
#include "src/models/Builder.hpp"

/**
 * @brief All different kinds of communication events.
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
