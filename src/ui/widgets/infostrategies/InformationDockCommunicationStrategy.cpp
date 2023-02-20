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
