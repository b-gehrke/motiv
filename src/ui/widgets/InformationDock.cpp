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
#include "TimeUnitLabel.hpp"
#include "src/utils.hpp"
#include <QPushButton>
#include <QFormLayout>
#include "InformationDock.hpp"



InformationDock::InformationDock(QWidget *parent) : QDockWidget(parent) {
    setWindowTitle(tr("Details"));
}

InformationDock::~InformationDock() {
    delete this->element_;
    for(auto &item : this->strategies_) {
        delete item.first;
        delete item.second;
    }
}

void InformationDock::updateView() {
    if(!element_) return;

    for (auto &item: strategies_) {
        auto widget = item.first;
        auto strategy = item.second;
        if(strategy->update(static_cast<QFormLayout *>(widget->layout()), element_)) {
            setWidget(widget);
            setWindowTitle("Details - " + QString::fromStdString(strategy->title()));
            break;
        }
    }
}

void InformationDock::zoomIntoViewPressed() {
    if(!element_) return;

    auto padding = element_->getDuration() / 10;

    Q_EMIT zoomToWindow(element_->getStartTime() - padding, element_->getEndTime() + padding);
}

void InformationDock::setElement(TimedElement *element) {
    element_ = element;

    updateView();
}

void InformationDock::addElementStrategy(InformationDockElementStrategy* s) {
    auto widget = new QWidget();
    auto layout = new QFormLayout(widget);
    layout->setAlignment(Qt::AlignLeading | Qt::AlignTop);

    s->setup(layout);

    auto zoomIntoViewButton = new QPushButton(tr("Zoom into &view"));
    connect(zoomIntoViewButton, SIGNAL(clicked()), this, SLOT(zoomIntoViewPressed()));
    layout->addWidget(zoomIntoViewButton);

    widget->setLayout(layout);

    strategies_.emplace_back(widget, s);
}
