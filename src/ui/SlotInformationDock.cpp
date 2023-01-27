#include "SlotInformationDock.hpp"

#include <QFormLayout>
#include <QPushButton>

#include "src/utils.hpp"
#include "TimeUnitLabel.hpp"

SlotInformationDock::SlotInformationDock(QWidget *parent) : QDockWidget(parent) {
    child = new QWidget(this);
    childLayout = new QFormLayout(child);
    childLayout->setAlignment(Qt::AlignLeading | Qt::AlignTop);
    child->setLayout(childLayout);
//    child->setMinimumWidth(200);

    nameField = new QLabel();
    rankField = new QLabel();
    startField = new TimeUnitLabel(0);
    endField = new TimeUnitLabel(0);
    runtimeField = new TimeUnitLabel(0);

    auto zoomIntoViewButton = new QPushButton(tr("Zoom into &view"));
    
    childLayout->addRow(tr("Name:"), nameField);
    childLayout->addRow(tr("Rank:"), rankField);
    childLayout->addRow(tr("Start:"), startField);
    childLayout->addRow(tr("End:"), endField);
    childLayout->addRow(tr("Runtime:"), runtimeField);

    childLayout->addWidget(zoomIntoViewButton);

    connect(zoomIntoViewButton, SIGNAL(clicked()), this, SLOT(zoomIntoViewPressed()));


    setWidget(child);
    setWindowTitle(tr("Details"));
}

void SlotInformationDock::updateView() {
    if(!slot_) return;

    auto name = QString::fromStdString(slot_->region->name().str());
    auto rank = QString::fromStdString(slot_->location->location_group().name().str());
    auto start = static_cast<double>(slot_->start.count());
    auto end = static_cast<double>(slot_->end.count());
    auto runtime = static_cast<double>(slot_->getDuration().count());

    nameField->setText(name);
    rankField->setText(rank);
    startField->setTime(start);
    endField->setTime(end);
    runtimeField->setTime(runtime);
}

void SlotInformationDock::setSlot(Slot* slot) {
    slot_ = slot;

    updateView();
}

void SlotInformationDock::zoomIntoViewPressed() {
    if(!slot_) return;

    Q_EMIT zoomToWindow(slot_->start, slot_->end);
}

