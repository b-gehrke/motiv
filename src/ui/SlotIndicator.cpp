#include "SlotIndicator.hpp"
#include "constants.hpp"
#include <QPen>
#include "SlotIndicator.hpp"

SlotIndicator::SlotIndicator(const QRectF &rect, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent) {
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
