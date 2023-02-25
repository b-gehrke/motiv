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
#include "InformationDockCollectiveCommunicationStrategy.hpp"
#include "src/utils.hpp"


void InformationDockCollectiveCommunicationStrategy::setup(QFormLayout *layout) {
    communicatorField = new QLabel;
    operationField = new QLabel;
    rootField = new QLabel;

    layout->addRow(tr("Communicator:"), communicatorField);
    layout->addRow(tr("Operation:"), operationField);
    layout->addRow(tr("Root:"), rootField);

    InformationDockElementBaseStrategy::setup(layout);
}

void InformationDockCollectiveCommunicationStrategy::updateView(QFormLayout *layout, CollectiveCommunicationEvent *element) {
    auto communicator = std::get<otf2::definition::comm>(*element->getCommunicator());

    auto collectiveRoot = static_cast<otf2::collective_root_type>(element->getRoot());

    QString rootName = "Unknown";
    switch(collectiveRoot) {
        case otf2::common::collective_root_type::none:
            rootName = "None";
            break;
        case otf2::common::collective_root_type::self:
            rootName = "Self";
            break;
        case otf2::common::collective_root_type::this_group:
            rootName = "This Group";
            break;
        default:
            if(holds_alternative<otf2::definition::comm_group>(communicator.group())) {
                auto group = get<otf2::definition::comm_group>(communicator.group());
                auto root = group[element->getRoot()];

                rootName = QString::fromStdString(root.name().str());
            }
            break;
    }

    auto operationName = QString::fromStdString(collectiveCommunicationOperationName(element->getOperation()));
    auto communicatorName = QString::fromStdString(communicator.name().str());

    rootField->setText(rootName);
    operationField->setText(operationName);
    communicatorField->setText(communicatorName);

    InformationDockElementBaseStrategy::updateView(layout, element);
}

std::string InformationDockCollectiveCommunicationStrategy::title() {
    return tr("Collective communication").toStdString();
}
