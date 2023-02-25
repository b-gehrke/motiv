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
#include <QGridLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include "FilterPopup.hpp"

FilterPopup::FilterPopup(const Filter &filter, QWidget *parent, const Qt::WindowFlags &f)
    : QDialog(parent, f), filter_(filter) {

    auto *grid = new QGridLayout();

    // Show checkboxes for different slot kinds
    auto slotKindsGroupBox = new QGroupBox(tr("Function calls"));
    mpiSlotKindCheckBox = new QCheckBox(tr("Show &MPI function calls"));
    mpiSlotKindCheckBox->setChecked(filter_.getSlotKinds() & SlotKind::MPI);
    openMpSlotKindCheckBox = new QCheckBox(tr("Show &OpenMp function calls"));
    openMpSlotKindCheckBox->setChecked(filter_.getSlotKinds() & SlotKind::OpenMP);
    plainSlotKindCheckBox = new QCheckBox(tr("Show &plain function calls"));
    plainSlotKindCheckBox->setChecked(filter_.getSlotKinds() & SlotKind::Plain);

    auto vbox = new QVBoxLayout();
    vbox->addWidget(mpiSlotKindCheckBox);
    vbox->addWidget(openMpSlotKindCheckBox);
    vbox->addWidget(plainSlotKindCheckBox);

    vbox->addStretch(1);
    slotKindsGroupBox->setLayout(vbox);

    grid->addWidget(slotKindsGroupBox, 0, 0);

    auto okButton = new QPushButton(tr("&Ok"));
    okButton->setDefault(true);
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    auto cancelButton = new QPushButton(tr("&Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    grid->addWidget(cancelButton, 1, 0, Qt::AlignLeft);
    grid->addWidget(okButton, 1, 1, Qt::AlignRight);


    connect(this, SIGNAL(accepted()), this, SLOT(updateFilter()));

    setLayout(grid);
    setWindowTitle(tr("Set filter"));
    setModal(true);
}

void FilterPopup::updateFilter() {
    auto slotKinds = static_cast<SlotKind>(
        SlotKind::Plain * plainSlotKindCheckBox->isChecked() |
        SlotKind::OpenMP * openMpSlotKindCheckBox->isChecked() |
        SlotKind::MPI * mpiSlotKindCheckBox->isChecked());

    filter_.setSlotKinds(slotKinds);

    Q_EMIT filterChanged(filter_);
}
