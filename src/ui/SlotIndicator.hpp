#ifndef MOTIV_SLOTINDICATOR_HPP
#define MOTIV_SLOTINDICATOR_HPP


#include <QGraphicsRectItem>

class SlotIndicator : public QGraphicsRectItem {
public:
    explicit SlotIndicator(const QRectF &rect, QGraphicsItem *parent = nullptr);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};


#endif //MOTIV_SLOTINDICATOR_HPP
