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
#ifndef MOTIV_CONSTANTS_HPP
#define MOTIV_CONSTANTS_HPP


namespace layers {
    const int Z_LAYER_HIGHLIGHTED_OFFSET = 20;
    const int Z_LAYER_P2P_COMMUNICATIONS = 100;
    const int Z_LAYER_COLLECTIVE_COMMUNICATIONS = 110;
    const int Z_LAYER_SLOTS_MIN_PRIORITY = 10;
    const int Z_LAYER_SLOTS_MAX_PRIORITY = Z_LAYER_SLOTS_MIN_PRIORITY + Z_LAYER_HIGHLIGHTED_OFFSET - 1;
    const int Z_LAYER_SELECTION = 200;
}

namespace colors {
    const QColor COLOR_SLOT_MPI = QColor::fromRgb(0xCDDC39);
    const QColor COLOR_SLOT_OPEN_MP = QColor::fromRgb(0xFF5722);
    const QColor COLOR_SLOT_PLAIN = QColor::fromRgb(0xBDBDBD);
    const QColor COLOR_COLLECTIVE_COMMUNICATION = QColor::fromRgb(0x42A5F5);
}

#endif //MOTIV_CONSTANTS_HPP
