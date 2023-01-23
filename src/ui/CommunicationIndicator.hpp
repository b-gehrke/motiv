#ifndef MOTIV_COMMUNICATIONINDICATOR_HPP
#define MOTIV_COMMUNICATIONINDICATOR_HPP

#include <QGraphicsPolygonItem>
#include <QPen>

class CommunicationIndicator : public QGraphicsPolygonItem {
public:
    CommunicationIndicator(QPointF from, QPointF to, qreal headLength = 10);
    CommunicationIndicator(qreal fromX, qreal fromY, qreal toX, qreal toY, qreal headLength = 10);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};


#endif //MOTIV_COMMUNICATIONINDICATOR_HPP
