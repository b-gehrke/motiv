#ifndef MOTIV_SLOTINDICATOR_HPP
#define MOTIV_SLOTINDICATOR_HPP


#include <QGraphicsRectItem>

#include "TraceDataProxy.hpp"

class SlotIndicator : public QGraphicsRectItem {
public:
    explicit SlotIndicator(const QRectF &rect, TraceDataProxy* data, Slot* representedSlot, QGraphicsItem *parent = nullptr);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    TraceDataProxy *data = nullptr;
    Slot *slot = nullptr;
};


#endif //MOTIV_SLOTINDICATOR_HPP
