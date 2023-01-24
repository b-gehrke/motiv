#include <QPen>
#include "SlotIndicator.hpp"

SlotIndicator::SlotIndicator(const QRectF &rect, TraceDataProxy* data, Slot* representedSlot, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent), data(data), slot(representedSlot) {
    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
}


void SlotIndicator::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QPen p(pen());
    p.setWidth(p.width() * 2);
    setPen(p);

    setZValue(zValue() + 10);

    QGraphicsItem::hoverEnterEvent(event);
}

void SlotIndicator::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QPen p(pen());
    p.setWidth(p.width() / 2);
    setPen(p);

    setZValue(zValue() - 10);

    QGraphicsItem::hoverLeaveEvent(event);
}

void SlotIndicator::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->data->setSlotSelection(this->slot);
    QGraphicsItem::mousePressEvent(event);
}
