#include "SlotIndicator.hpp"

#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "src/ui/Constants.hpp"

SlotIndicator::SlotIndicator(const QRectF &rect, Slot *representedSlot, QGraphicsItem *parent)
    : GenericIndicator<Slot, QGraphicsRectItem>(representedSlot, parent) {
    setRect(rect);
}
