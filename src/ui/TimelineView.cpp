#include "TimelineView.hpp"

#include <QGraphicsRectItem>

TimelineView::TimelineView(TraceDataProxy *data, QWidget *parent) : QGraphicsView(parent), data(data) {
    auto scene = new QGraphicsScene(this);
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->setAutoFillBackground(false);
    this->setStyleSheet("background: transparent");
    this->setScene(scene);

    populateScene(scene);

    connect(this->data, SIGNAL(selectionChanged()), this, SLOT(updateView()));
}

void TimelineView::populateScene(QGraphicsScene *scene) {
    auto width = scene->width();
    auto selection = this->data->getSelection();
    auto runtime = selection->getRuntime().count();
    auto begin = this->data->getBegin().count();

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

            auto slotBeginPos = qMin(0.0, (static_cast<qreal>(startTime - begin) / static_cast<qreal>(runtime)) * width);

            auto slotRuntime = static_cast<qreal>(endTime - startTime);
            auto rectWidth = (slotRuntime / static_cast<qreal>(runtime)) * width;
            rectWidth = qMin(rectWidth, static_cast<qreal>(width - slotBeginPos));

            QRectF rect(slotBeginPos, top, qMax(rectWidth, 5.0), ROW_HEIGHT);
            auto rectItem = scene->addRect(rect);
            rectItem->setToolTip(regionNameStr.c_str());

            // Determine color based on name
            QColor rectColor;
            if(regionNameStr.starts_with("MPI_")) {
                rectColor = Qt::green;
                rectItem->setZValue(3);
            } else if(regionNameStr.starts_with("!$omp")) {
                rectColor = Qt::red;
                rectItem->setZValue(2);
            } else {
                rectColor = Qt::lightGray;
                rectItem->setZValue(1);
            }
            rectItem->setBrush(rectColor);
        }

        top += ROW_HEIGHT;
    }
}

void TimelineView::resizeEvent(QResizeEvent *event) {
    this->updateView();
    QGraphicsView::resizeEvent(event);
}

void TimelineView::updateView() {
    // TODO it might be more performant to keep track of items and add/remove new/leaving items and resizing them
    delete this->scene();
    auto scene = new QGraphicsScene(this);

    auto ROW_HEIGHT = 30;
    auto sceneHeight = this->data->getSelection()->getSlots().size() * ROW_HEIGHT;
    auto sceneRect = this->rect();
    sceneRect.setHeight(sceneHeight);

    scene->setSceneRect(sceneRect);
    this->populateScene(scene);
    this->setScene(scene);
}
