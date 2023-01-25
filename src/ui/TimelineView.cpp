#include "TimelineView.hpp"
#include "CommunicationIndicator.hpp"
#include "SlotIndicator.hpp"
#include "constants.hpp"

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

    connect(this->data, SIGNAL(selectionChanged()), this, SLOT(updateView()));
    connect(this->data, SIGNAL(filterChanged(Filter)), this, SLOT(updateView()));
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
    QPen collectiveCommunicationPen(Qt::blue, 2);


    auto top = 20;
    auto ROW_HEIGHT = 30;
    for (const auto &item: selection->getSlots()) {
        // Display slots
        for (const auto &slot: item.second) {
            if(!(slot->getKind() & data->getSettings()->getFilter().getSlotKinds())) continue;

            auto region = slot->region;
            auto regionName = region->name();
            auto regionNameStr = regionName.str();
            auto startTime = slot->start.count();
            auto endTime = slot->end.count();


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
            auto rectItem = new SlotIndicator(rect, this->data, slot);
            rectItem->setOnSelected(
                [this](Slot *selectedSlot) { this->data->setSelection(selectedSlot->start, selectedSlot->end); });
            rectItem->setToolTip(regionNameStr.c_str());

            // Determine color based on name
            QColor rectColor;
            if (regionNameStr.starts_with("MPI_")) {
                rectColor = Qt::green;
                rectItem->setZValue(layers::Z_LAYER_SLOTS_MIN_PRIORITY + 2);
            } else if (regionNameStr.starts_with("!$omp")) {
                rectColor = Qt::red;
                rectItem->setZValue(layers::Z_LAYER_SLOTS_MIN_PRIORITY + 1);
            } else {
                rectColor = Qt::lightGray;
                rectItem->setZValue(layers::Z_LAYER_SLOTS_MIN_PRIORITY + 0);
            }
            rectItem->setBrush(rectColor);
            scene->addItem(rectItem);
        }

        top += ROW_HEIGHT;
    }

    for (const auto &communication: selection->getCommunications()) {
        const CommunicationEvent *startEvent = communication->getStart();
        auto startEventEnd = static_cast<qreal>(startEvent->getEnd().count());
        auto startEventStart = static_cast<qreal>(startEvent->getStart().count());


        const CommunicationEvent *endEvent = communication->getEnd();
        auto endEventEnd = static_cast<qreal>(startEvent->getEnd().count());
        auto endEventStart = static_cast<qreal>(startEvent->getStart().count());


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

        auto arrow = new CommunicationIndicator(fromX, fromY, toX, toY);
        arrow->setPen(arrowPen);
        arrow->setZValue(layers::Z_LAYER_P2P_COMMUNICATIONS);
        scene->addItem(arrow);
    }

    for (const auto &communication: selection->getCollectiveCommunications()) {
        auto fromTime = static_cast<qreal>(communication->getStart().count());
        auto effectiveFromTime = qMax(beginR, fromTime) - beginR;

        auto toTime = static_cast<qreal>(communication->getEnd().count());
        auto effectiveToTime = qMin(endR, toTime) - beginR;

        auto fromX = (effectiveFromTime / runtimeR) * width;
        auto fromY = 10;

        auto toX = (effectiveToTime / runtimeR) * width;
        auto toY = top + 10;

        QRectF rect(QPointF(fromX, fromY), QPointF(toX, toY));
        auto rectItem = scene->addRect(rect);
        rectItem->setPen(collectiveCommunicationPen);
        rectItem->setZValue(layers::Z_LAYER_COLLECTIVE_COMMUNICATIONS);
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
            newBegin = data->getSelection()->getStartTime() - deltaDuration;
            newEnd = data->getSelection()->getStartTime() + data->getSelection()->getRuntime() - deltaDuration;
        }

        data->setSelection(newBegin, newEnd);
        event->accept();
    }

    QGraphicsView::wheelEvent(event);
}
