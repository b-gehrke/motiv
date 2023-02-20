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
