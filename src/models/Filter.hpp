/*
 * Marvellous OTF2 Traces Interactive Visualizer (MOTIV)
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
#ifndef MOTIV_FILTER_HPP
#define MOTIV_FILTER_HPP

#define FILTER_DEFAULT ((SlotKind) (SlotKind::MPI | SlotKind::OpenMP | SlotKind::Plain))

#include "Slot.hpp"

class Filter {
public: // constructors

public: // methods
    [[nodiscard]] SlotKind getSlotKinds() const;

    void setSlotKinds(SlotKind slotKinds);

private: // fields
    SlotKind slotKinds_ = FILTER_DEFAULT;
};


#endif //MOTIV_FILTER_HPP
