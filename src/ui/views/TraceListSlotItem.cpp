#include "TraceListSlotItem.hpp"

TraceListSlotItem::TraceListSlotItem(Slot *slot, TraceDataModel *model, QGraphicsItem *parent) : slot(slot), data(model) {

}

void TraceListSlotItem::mousePressEvent(QGraphicsSceneMouseEvent *click) {
//    QGraphicsItem::mousePressEvent(click);
    qDebug() << "Clicked" << slot->region.name().str().c_str();
}
