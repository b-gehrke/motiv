#include "SlotIndicator.hpp"
#include "constants.hpp"
#include <QPen>
#include <QGraphicsSceneMouseEvent>

SlotIndicator::SlotIndicator(const QRectF &rect, Slot *slot, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent),
                                                                                      slot_(slot) {
    setAcceptHoverEvents(true);
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
