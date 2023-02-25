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
#include "TimelineLabelList.hpp"

#include <QLabel>
#include <QSizePolicy>
#include <QVBoxLayout>

TimelineLabelList::TimelineLabelList(TraceDataProxy *data, QWidget *parent) : QListWidget(parent), data(data) {
    this->setFrameShape(QFrame::NoFrame);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet("background: transparent");
    setViewportMargins(0, 20,0,0);

    for (const auto &ranks : this->data->getSelection()->getSlots()) {
        const auto &rankName = ranks.first->name().str();
        auto item = new QListWidgetItem(this);
        item->setText(QString::fromStdString(rankName));
        item->setSizeHint(QSize(0, 30 /* TODO ROW_HEIGHT */));
        item->setTextAlignment(Qt::AlignCenter);
        this->addItem(item);
    }
}

void TimelineLabelList::mousePressEvent(QMouseEvent *event) {
    return;
}

void TimelineLabelList::mouseReleaseEvent(QMouseEvent *event) {
    return;
}

void TimelineLabelList::mouseMoveEvent(QMouseEvent *event) {
    return;
}
