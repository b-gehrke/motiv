#include "SlotIndicator.hpp"

#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "src/ui/Constants.hpp"

SlotIndicator::SlotIndicator(const QRectF &rect, Slot *representedSlot, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent), slot_(representedSlot) {
    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
}

void SlotIndicator::setOnDoubleClick(const std::function<void(Slot *)>& fn) {
    onDoubleClick = fn;
}

void SlotIndicator::setOnSelected(const std::function<void(Slot *)>& fn) {
    onSelected = fn;
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
    if (onDoubleClick) {
        onDoubleClick(slot_);
        event->accept();
    }
}

void SlotIndicator::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (onSelected) {
        onSelected(slot_);
        event->accept();
    }
}
