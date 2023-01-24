#include "SlotIndicator.hpp"

#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "constants.hpp"

SlotIndicator::SlotIndicator(const QRectF &rect, TraceDataProxy* data, Slot* representedSlot, QGraphicsItem *parent)
: QGraphicsRectItem(rect, parent), data(data), slot_(representedSlot) {
    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
}


void SlotIndicator::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QPen p(pen());
    p.setWidth(p.width() * 2);
    setPen(p);

    setZValue(zValue() + layers::Z_LAYER_HIGHLIGHTED_OFFSET);

    QGraphicsItem::hoverEnterEvent(event);
}

void SlotIndicator::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QPen p(pen());
    p.setWidth(p.width() / 2);
    setPen(p);

    setZValue(zValue() - layers::Z_LAYER_HIGHLIGHTED_OFFSET);

    QGraphicsItem::hoverLeaveEvent(event);
}

void SlotIndicator::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    // This event is fired again for overlapping elements. Only consider the top (visible) one.
    if (onSelected && isUnderMouse()) {
        onSelected(slot_);
        event->accept();
    }


    QGraphicsItem::mouseDoubleClickEvent(event);
}

void SlotIndicator::setOnSelected(std::function<void(Slot *)> fn) {
    onSelected = std::move(fn);
}

void SlotIndicator::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (this->isUnderMouse()) {
        this->data->setSlotSelection(this->slot_);
    }
    QGraphicsItem::mousePressEvent(event);
}
