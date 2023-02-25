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
#include "TimelineView.hpp"
#include "src/ui/views/CommunicationIndicator.hpp"
#include "src/ui/views/SlotIndicator.hpp"
#include "src/ui/Constants.hpp"
#include "CollectiveCommunicationIndicator.hpp"

#include <QGraphicsRectItem>
#include <QApplication>
#include <QWheelEvent>

TimelineView::TimelineView(TraceDataProxy *data, QWidget *parent) : QGraphicsView(parent), data(data) {
    auto scene = new QGraphicsScene(this);
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->setAutoFillBackground(false);
    this->setStyleSheet("background: transparent");
    this->setScene(scene);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // @formatter:off
    connect(this->data, SIGNAL(selectionChanged(types::TraceTime,types::TraceTime)), this, SLOT(updateView()));
    connect(this->data, SIGNAL(filterChanged(Filter)), this, SLOT(updateView()));
    // @formatter:on
}


void TimelineView::populateScene(QGraphicsScene *scene) {
    auto width = scene->width();
    auto selection = this->data->getSelection();
    auto runtime = selection->getRuntime().count();
    auto runtimeR = static_cast<qreal>(runtime);
    auto begin = this->data->getBegin().count();
    auto beginR = static_cast<qreal>(begin);
    auto end = begin + runtime;
    auto endR = static_cast<qreal>(end);

    QPen arrowPen(Qt::black, 1);
    QPen collectiveCommunicationPen(colors::COLOR_COLLECTIVE_COMMUNICATION, 2);


    auto onTimedElementSelected = [this](TimedElement *element) { this->data->setTimeElementSelection(element); };
    auto onTimedElementDoubleClicked = [this](TimedElement *element) {
        this->data->setSelection(element->getStartTime(), element->getEndTime());
    };


    auto top = 20;
    auto ROW_HEIGHT = 30;
    for (const auto &item: selection->getSlots()) {
        // Display slots
        for (const auto &slot: item.second) {
            if (!(slot->getKind() & data->getSettings()->getFilter().getSlotKinds())) continue;

            auto region = slot->region;
            auto regionName = region->name();
            auto regionNameStr = regionName.str();
            auto startTime = slot->startTime.count();
            auto endTime = slot->endTime.count();


            // Ensures slots starting before `begin` (like main) are considered to start at begin
            auto effectiveStartTime = qMax(begin, startTime);
            // Ensures slots ending after `end` (like main) are considered to end at end
            auto effectiveEndTime = qMin(end, endTime);

            auto slotBeginPos = qMax(0.0,
                                     (static_cast<qreal>(effectiveStartTime - begin) / static_cast<qreal>(runtime)) *
                                     width);
            auto slotRuntime = static_cast<qreal>(effectiveEndTime - effectiveStartTime);
            auto rectWidth = (slotRuntime / static_cast<qreal>(runtime)) * width;

            QRectF rect(slotBeginPos, top, qMax(rectWidth, 5.0), ROW_HEIGHT);
            auto rectItem = new SlotIndicator(rect, slot);
            rectItem->setOnDoubleClick(onTimedElementDoubleClicked);
            rectItem->setOnSelected(onTimedElementSelected);
            rectItem->setToolTip(regionNameStr.c_str());

            // Determine color based on name
            QColor rectColor;
            if (regionNameStr.starts_with("MPI_")) {
                rectColor = colors::COLOR_SLOT_MPI;
                rectItem->setZValue(layers::Z_LAYER_SLOTS_MIN_PRIORITY + 2);
            } else if (regionNameStr.starts_with("!$omp")) {
                rectColor = colors::COLOR_SLOT_OPEN_MP;
                rectItem->setZValue(layers::Z_LAYER_SLOTS_MIN_PRIORITY + 1);
            } else {
                rectColor = colors::COLOR_SLOT_PLAIN;
                rectItem->setZValue(layers::Z_LAYER_SLOTS_MIN_PRIORITY + 0);
            }
            rectItem->setBrush(rectColor);
            scene->addItem(rectItem);
        }

        top += ROW_HEIGHT;
    }

    for (const auto &communication: selection->getCommunications()) {
        const CommunicationEvent *startEvent = communication->getStartEvent();
        auto startEventEnd = static_cast<qreal>(startEvent->getEndTime().count());
        auto startEventStart = static_cast<qreal>(startEvent->getStartTime().count());


        const CommunicationEvent *endEvent = communication->getEndEvent();
        auto endEventEnd = static_cast<qreal>(startEvent->getEndTime().count());
        auto endEventStart = static_cast<qreal>(startEvent->getStartTime().count());


        auto fromTime = startEventStart + (startEventEnd - startEventStart) / 2;
        auto effectiveFromTime = qMax(beginR, fromTime) - beginR;

        auto toTime = endEventStart + (endEventEnd - endEventStart) / 2;
        auto effectiveToTime = qMin(endR, toTime) - beginR;

        auto fromRank = startEvent->getLocation()->ref().get();
        auto toRank = endEvent->getLocation()->ref().get();

        auto fromX = effectiveFromTime / runtimeR * width;
        auto fromY = static_cast<qreal>(fromRank * ROW_HEIGHT) + .5 * ROW_HEIGHT + 20;

        auto toX = effectiveToTime / runtimeR * width;
        auto toY = static_cast<qreal> (toRank * ROW_HEIGHT) + .5 * ROW_HEIGHT + 20;

        auto arrow = new CommunicationIndicator(communication, fromX, fromY, toX, toY);
        arrow->setOnSelected(onTimedElementSelected);
        arrow->setOnDoubleClick(onTimedElementDoubleClicked);
        arrow->setPen(arrowPen);
        arrow->setZValue(layers::Z_LAYER_P2P_COMMUNICATIONS);
        scene->addItem(arrow);
    }

    for (const auto &communication: selection->getCollectiveCommunications()) {
        auto fromTime = static_cast<qreal>(communication->getStartTime().count());
        auto effectiveFromTime = qMax(beginR, fromTime) - beginR;

        auto toTime = static_cast<qreal>(communication->getEndTime().count());
        auto effectiveToTime = qMin(endR, toTime) - beginR;

        auto fromX = (effectiveFromTime / runtimeR) * width;
        auto fromY = 10;

        auto toX = (effectiveToTime / runtimeR) * width;
        auto toY = top + 10;

        auto rectItem = new CollectiveCommunicationIndicator(communication);
        rectItem->setOnSelected(onTimedElementSelected);
        rectItem->setRect(QRectF(QPointF(fromX, fromY), QPointF(toX, toY)));
        rectItem->setPen(collectiveCommunicationPen);
        rectItem->setZValue(layers::Z_LAYER_COLLECTIVE_COMMUNICATIONS);
        scene->addItem(rectItem);
    }

}


void TimelineView::resizeEvent(QResizeEvent *event) {
    this->updateView();
    QGraphicsView::resizeEvent(event);
}

void TimelineView::updateView() {
    // TODO it might be more performant to keep track of items and add/remove new/leaving items and resizing them
//    delete this->scene();
    auto scene = new QGraphicsScene(this);

    auto ROW_HEIGHT = 30;
    auto sceneHeight = this->data->getSelection()->getSlots().size() * ROW_HEIGHT;
    auto sceneRect = this->rect();
    sceneRect.setHeight(sceneHeight);

    scene->setSceneRect(sceneRect);
    this->populateScene(scene);
    this->setScene(scene);
}

void TimelineView::wheelEvent(QWheelEvent *event) {
    // Calculation according to https://doc.qt.io/qt-6/qwheelevent.html#angleDelta:
    // @c angleDelta is in eights of a degree and most mouse wheels work in steps of 15 degrees.
    QPoint numDegrees = event->angleDelta() / 8;

    if (!numDegrees.isNull() && QApplication::keyboardModifiers() & (Qt::CTRL | Qt::SHIFT)) {
        // See documentation and comment above
        QPoint numSteps = numDegrees / 15;
        auto stepSize = data->getSelection()->getRuntime() / data->getSettings()->getZoomQuotient();
        auto deltaDuration = stepSize * numSteps.y();
        auto delta = static_cast<double>(deltaDuration.count());

        types::TraceTime newBegin;
        types::TraceTime newEnd;
        if (QApplication::keyboardModifiers() == Qt::CTRL) {
            // Calculate the position of the mouse relative to the scene to zoom to where the mouse is pointed
            auto originFactor = event->scenePosition().x() / this->scene()->width();

            auto leftDelta = types::TraceTime(static_cast<long>(originFactor * 2 * delta));
            auto rightDelta = types::TraceTime(static_cast<long>((1 - originFactor) * 2 * delta));

            newBegin = data->getSelection()->getStartTime() + leftDelta;
            newEnd = data->getSelection()->getStartTime() + data->getSelection()->getRuntime() - rightDelta;
        } else {
            // Calculate new absolute times (might be negative or to large)
            auto newBeginAbs = data->getSelection()->getStartTime() - deltaDuration;
            auto newEndAbs = data->getSelection()->getStartTime() + data->getSelection()->getRuntime() - deltaDuration;

            // Limit the times to their boundaries (0 for start and end of entire trace for end)
            auto newBeginBounded = qMax(newBeginAbs, types::TraceTime(0));
            auto newEndBounded = qMin(newEndAbs, data->getTotalRuntime());

            // If one time exceeds the bounds reject the changes
            newBegin = qMin(newBeginBounded, newEndBounded - data->getSelection()->getRuntime());
            newEnd = qMax(newEndBounded, newBeginBounded + data->getSelection()->getRuntime());
        }

        data->setSelection(newBegin, newEnd);
        event->accept();
    }

    QGraphicsView::wheelEvent(event);
}
