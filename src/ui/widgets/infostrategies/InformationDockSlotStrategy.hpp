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
#ifndef MOTIV_INFORMATIONDOCKSLOTSTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKSLOTSTRATEGY_HPP


#include "InformationDockElementBaseStrategy.hpp"
#include "src/models/Slot.hpp"

class InformationDockSlotStrategy : public InformationDockElementBaseStrategy<Slot> {
public:
    void setup(QFormLayout *layout) override;

    void updateView(QFormLayout *layout, Slot *element) override;

    std::string title() override;

private:
    QLabel *nameField = nullptr;
    QLabel *rankField = nullptr;

};


#endif //MOTIV_INFORMATIONDOCKSLOTSTRATEGY_HPP
