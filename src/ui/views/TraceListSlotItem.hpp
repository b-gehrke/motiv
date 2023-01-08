#ifndef MOTIV_TRACELISTSLOTITEM_HPP
#define MOTIV_TRACELISTSLOTITEM_HPP


#include <QGraphicsRectItem>
#include "src/models/slot.hpp"
#include "src/ui/TraceDataModel.hpp"

class TraceListSlotItem : public QGraphicsRectItem {
public: //constructors
    explicit TraceListSlotItem(Slot *slot, TraceDataModel *model, QGraphicsItem *parent = nullptr);

public Q_SLOTS:
    void mousePressEvent(QGraphicsSceneMouseEvent *click) override;

private:
    // Slot represented by this item
    Slot *slot = nullptr;
    TraceDataModel *data = nullptr;
};


#endif //MOTIV_TRACELISTSLOTITEM_HPP
