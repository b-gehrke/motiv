#ifndef MOTIV_SLOTINDICATOR_HPP
#define MOTIV_SLOTINDICATOR_HPP


#include <QGraphicsRectItem>

#include "src/ui/TraceDataProxy.hpp"
#include "src/models/Slot.hpp"
#include "src/types.h"

class SlotIndicator : public QGraphicsRectItem {
public: // constructors
    SlotIndicator(const QRectF &rect, Slot* representedSlot, QGraphicsItem *parent = nullptr);

public: // methods
    void setOnDoubleClick(const std::function<void(Slot *)>& fn);
    void setOnSelected(const std::function<void(Slot *)>& fn);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Slot* slot_;

private: // event handler
    std::function<void(Slot*)> onDoubleClick;
    std::function<void(Slot *pSlot)>  onSelected;
};


#endif //MOTIV_SLOTINDICATOR_HPP
