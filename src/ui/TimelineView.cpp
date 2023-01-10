#include "TimelineView.hpp"

#include <QGraphicsRectItem>

TimelineView::TimelineView(TraceDataProxy *data, QWidget *parent) : QGraphicsView(parent), data(data) {
    auto scene = new QGraphicsScene(this);
    this->setAutoFillBackground(false);
    this->setStyleSheet("background: transparent");
    this->setScene(scene);

    populateScene();
}

void TimelineView::populateScene() {
    auto scene = this->scene();
    auto width = scene->width();
    auto selection = this->data->getSelection();
    auto runtime = selection->getRuntime().count();
    auto begin = this->data->getBegin().count();
    auto end = this->data->getEnd().count();

    auto top = 0;
    auto ROW_HEIGHT = 30;
    for (const auto& item : selection->getSlots()) {
        // Display slots
        for (const auto& slot : item.second) {
            auto region = slot->region;
            auto regionName = region->name();
            auto regionNameStr = regionName.str();
            auto startTime = slot->start.count();
            auto endTime = slot->end.count();

            auto slotBeginPos = (static_cast<qreal>(startTime - begin) / static_cast<qreal>(runtime)) * width;

            auto slotRuntime = static_cast<qreal>(endTime - startTime);
            auto rectWidth = (slotRuntime / static_cast<qreal>(runtime)) * width;
            rectWidth = qMin(rectWidth, static_cast<qreal>(width - slotBeginPos - 1));

            QRectF rect(slotBeginPos, top, qMax(rectWidth, 5.0), ROW_HEIGHT);
            auto rectItem = scene->addRect(rect);
            rectItem->setToolTip(regionNameStr.c_str());
            rectItem->setZValue(1);

            // Determine color based on name
            QColor rectColor;
            if(regionNameStr.starts_with("MPI_")) {
                rectColor = Qt::green;
            } else if(regionNameStr.starts_with("!$omp")) {
                rectColor = Qt::red;
            } else {
                rectColor = Qt::lightGray;
            }
            rectItem->setBrush(rectColor);
        }

        top += ROW_HEIGHT;
    }
}
