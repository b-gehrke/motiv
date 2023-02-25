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
#include "Timeline.hpp"
#include "src/ui/ScrollSynchronizer.hpp"

#include <QGridLayout>

Timeline::Timeline(TraceDataProxy *data, QWidget *parent) : QWidget(parent), data(data) {
    auto layout = new QGridLayout(this);

    this->header = new TimelineHeader(this->data, this);
    layout->addWidget(this->header, 0, 1);

    this->labelList = new TimelineLabelList(this->data, this);
    layout->addWidget(this->labelList, 1, 0);

    this->view = new TimelineView(this->data, this);
    layout->addWidget(this->view, 1, 1);

    // This prevents the labelList from expanding to 50% of the width.
    // Not really a satisfactory solution.
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 9);

    auto scrollSyncer = new ScrollSynchronizer(this);
    scrollSyncer->addWidget(this->labelList);
    scrollSyncer->addWidget(this->view);
}
