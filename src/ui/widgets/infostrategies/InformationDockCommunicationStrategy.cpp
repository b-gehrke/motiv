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
#include "InformationDockCommunicationStrategy.hpp"
#include "src/utils.hpp"

void InformationDockCommunicationStrategy::setup(QFormLayout *layout) {
    communicatorField = new QLabel;
    startKindField = new QLabel;
    endKindField = new QLabel;
    rankFromField = new QLabel;
    rankToField = new QLabel;

    layout->addRow(tr("From:"), rankFromField);
    layout->addRow(tr("To:"), rankToField);
    layout->addRow(tr("Communicator:"), communicatorField);
    layout->addRow(tr("Start event:"), startKindField);
    layout->addRow(tr("End event:"), endKindField);

    InformationDockElementBaseStrategy::setup(layout);
}

void InformationDockCommunicationStrategy::updateView(QFormLayout *layout, Communication *element) {
    auto communicator = std::get<otf2::definition::comm>(*element->getStartEvent()->getCommunicator());
    auto startEvent = element->getStartEvent();
    auto endEvent = element->getEndEvent();

    auto rankFrom = QString::fromStdString(startEvent->getLocation()->location_group().name().str());
    auto rankTo = QString::fromStdString(endEvent->getLocation()->location_group().name().str());
    auto startKindName = QString::fromStdString(communicationKindName(startEvent->getKind()));
    auto endKindName = QString::fromStdString(communicationKindName(endEvent->getKind()));
    auto communicatorName = QString::fromStdString(communicator.name().str());

    rankFromField->setText(rankFrom);
    rankToField->setText(rankTo);
    startKindField->setText(startKindName);
    endKindField->setText(endKindName);
    communicatorField->setText(communicatorName);
    
    InformationDockElementBaseStrategy::updateView(layout, element);
}

std::string InformationDockCommunicationStrategy::title() {
    return tr("P2P communication").toStdString();
}
