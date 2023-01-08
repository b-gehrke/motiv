#include "TraceListScene.hpp"

static const double MIN_SLOT_WIDTH = 5.0;

TraceListSlotItem *TraceListScene::addSlot(Slot *slot) {
    auto region_name = slot->region.name().str();
    auto startTime = slot->start;
    auto endTime = slot->end;

    auto slotBeginPos = (leadingMargin + yAxisWidth)
                        + (static_cast<qreal>(startTime.count() - selectionBegin) / static_cast<qreal>(selectionRuntime)) * canvasWidth();

    auto slotRuntime = static_cast<qreal>((endTime - startTime).count());
    auto rectWidth = (slotRuntime / static_cast<qreal>(selectionRuntime)) * canvasWidth();
//            rectWidth = qMin(rectWidth, static_cast<qreal>(sceneWidth - slotBeginPos - 1));

    qDebug() << region_name.c_str() << slotBeginPos << canvasWidth() << rectWidth;

    QRectF rect(slotBeginPos, top, qMax(rectWidth, MIN_SLOT_WIDTH), rowHeight);
    auto rectItem = addRect(rect);
    rectItem->setToolTip(region_name.c_str());
    rectItem->setZValue(1);

    // Determine color based on name
    QColor rectColor;
    if(region_name.starts_with("MPI_")) {
        rectColor = Qt::green;
    } else if(region_name.starts_with("!$omp")) {
        rectColor = Qt::red;
    } else {
        rectColor = Qt::lightGray;
    }
    rectItem->setBrush(rectColor);
}
