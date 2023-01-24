#ifndef MOTIV_SLOTINDICATOR_HPP
#define MOTIV_SLOTINDICATOR_HPP


#include <QGraphicsRectItem>
#include "src/models/slot.hpp"
#include "src/types.h"

class SlotIndicator : public QGraphicsRectItem {
public: // constructors
    explicit SlotIndicator(const QRectF &rect, Slot* slot, QGraphicsItem *parent = nullptr);

public: // methods
    void setOnSelected(std::function<void(Slot *)> onSelected);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Slot* slot_;
    std::function<void(Slot*)> onSelected;
};


#endif //MOTIV_SLOTINDICATOR_HPP
