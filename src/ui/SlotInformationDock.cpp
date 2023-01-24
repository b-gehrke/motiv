#include "SlotInformationDock.hpp"

#include <QFormLayout>

#include "src/utils.hpp"
#include "TimeUnitLabel.hpp"

SlotInformationDock::SlotInformationDock(TraceDataProxy *data, QWidget *parent) : QDockWidget(parent), data(data) {
    auto child = new QWidget(this);
    this->setWidget(child);
    auto childLayout = new QFormLayout(child);
    childLayout->setAlignment(Qt::AlignLeading | Qt::AlignTop);
    child->setLayout(childLayout);

    connect(data, &TraceDataProxy::slotSelectionChanged, this, &SlotInformationDock::updateInformation);

    this->updateInformation();
}

void SlotInformationDock::addInformation() {
    auto slot = this->data->getSelectedSlot();
    auto name = QString::fromStdString(slot->region->name().str());
    auto rank = QString::fromStdString(slot->location->location_group().name().str());
    auto start = slot->start.count();
    auto end = slot->end.count();
    auto runtime = slot->getDuration().count();

    // TODO this seems redundant
    auto child = new QWidget(this);
    this->setWidget(child);
    auto childLayout = new QFormLayout(child);
    childLayout->setAlignment(Qt::AlignLeading | Qt::AlignTop);
    child->setLayout(childLayout);

    auto layout = childLayout;

    layout->addRow(tr("Name:"), new QLabel(name, this));
    layout->addRow(tr("Rank:"), new QLabel(rank, this));
    layout->addRow(tr("Start:"), new TimeUnitLabel(start, this));
    layout->addRow(tr("End:"), new TimeUnitLabel(end, this));
    layout->addRow(tr("Runtime:"), new TimeUnitLabel(runtime, this));
}

void SlotInformationDock::clearInformation() {
    resetLayout(this->layout());
}

void SlotInformationDock::updateInformation() {
    if (this->data->getSelectedSlot()) {
        this->clearInformation();
        this->addInformation();
    }
//    this->close();
}

