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
#include "utils.hpp"

void resetLayout(QLayout *apLayout) {
    if(!apLayout) return;
    QLayoutItem *vpItem;
    while ((vpItem = apLayout->takeAt(0)) != 0) {
        if (vpItem->layout()) {
            resetLayout(vpItem->layout());
            vpItem->layout()->deleteLater();
        }
        if (vpItem->widget()) {
            vpItem->widget()->deleteLater();
        }
        delete vpItem;
    }
}


std::string communicationKindName(CommunicationKind kind) {
    switch (kind) {
        case BlockingSend:
            return "Blocking send";
        case BlockingReceive:
            return "Blocking receive";
        case NonBlockingSend:
            return "Non-blocking send";
        case NonBlockingReceive:
            return "Non-blocking receive";
        case Collective:
            return "Collective";
        case RequestCancelled:
            return "Request cancelled";
        default:
            throw std::invalid_argument("Invalid communication kind");
    }
}

std::string collectiveCommunicationOperationName(otf2::collective_type type) {
    switch (type) {
        case otf2::common::collective_type::barrier:
            return "Barrier";
        case otf2::common::collective_type::broadcast:
            return "Broadcast";
        case otf2::common::collective_type::gather:
            return "Gather";
        case otf2::common::collective_type::gatherv:
            return "Gatherv";
        case otf2::common::collective_type::scatter:
            return "Scatter";
        case otf2::common::collective_type::scatterv:
            return "Scatterv";
        case otf2::common::collective_type::all_gather:
            return "All Gather";
        case otf2::common::collective_type::all_gatherv:
            return "All Gatherv";
        case otf2::common::collective_type::all_to_all:
            return "All To All";
        case otf2::common::collective_type::all_to_allv:
            return "All To Allv";
        case otf2::common::collective_type::all_to_allw:
            return "All To Allw";
        case otf2::common::collective_type::all_reduce:
            return "All Reduce";
        case otf2::common::collective_type::reduce:
            return "Reduce";
        case otf2::common::collective_type::reduce_scatter:
            return "Reduce Scatter";
        case otf2::common::collective_type::scan:
            return "Scan";
        case otf2::common::collective_type::exscan:
            return "Exscan";
        case otf2::common::collective_type::reduce_scatter_block:
            return "Reduce Scatter Block";
        case otf2::common::collective_type::create_handle:
            return "Create Handle";
        case otf2::common::collective_type::destroy_handle:
            return "Destroy Handle";
        case otf2::common::collective_type::allocate:
            return "Allocate";
        case otf2::common::collective_type::deallocate:
            return "Deallocate";
        case otf2::common::collective_type::create_handle_and_allocate:
            return "Create Handle And Allocate";
        case otf2::common::collective_type::destroy_handle_and_deallocate:
            return "Destroy Handle And Deallocate";
        default:
            throw std::invalid_argument("Invalid operation type");
    }
}
