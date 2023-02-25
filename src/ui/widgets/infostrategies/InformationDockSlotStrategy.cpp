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
#include "InformationDockSlotStrategy.hpp"


void InformationDockSlotStrategy::updateView(QFormLayout *layout, Slot *element) {
    auto name = QString::fromStdString(element->region->name().str());
    auto rank = QString::fromStdString(element->location->location_group().name().str());

    nameField->setText(name);
    rankField->setText(rank);

    InformationDockElementBaseStrategy<Slot>::updateView(layout, element);
}

void InformationDockSlotStrategy::setup(QFormLayout *layout) {
    nameField = new QLabel();
    rankField = new QLabel();

    layout->addRow(tr("Name:"), nameField);
    layout->addRow(tr("Rank:"), rankField);


    InformationDockElementBaseStrategy<Slot>::setup(layout);
}

std::string InformationDockSlotStrategy::title() {
    return tr("Region (Function)").toStdString();
}
