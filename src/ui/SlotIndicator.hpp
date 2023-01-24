#ifndef MOTIV_SLOTINDICATOR_HPP
#define MOTIV_SLOTINDICATOR_HPP


#include <QGraphicsRectItem>

#include "TraceDataProxy.hpp"
#include "src/models/slot.hpp"
#include "src/types.h"

class SlotIndicator : public QGraphicsRectItem {
public: // constructors
    SlotIndicator(const QRectF &rect, TraceDataProxy* data, Slot* representedSlot, QGraphicsItem *parent = nullptr);

public: // methods
    void setOnSelected(std::function<void(Slot *)> onSelected);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Slot* slot_;
    TraceDataProxy *data;
    std::function<void(Slot*)> onSelected;

};


#endif //MOTIV_SLOTINDICATOR_HPP
