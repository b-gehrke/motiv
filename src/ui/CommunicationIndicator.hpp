#ifndef MOTIV_COMMUNICATIONINDICATOR_HPP
#define MOTIV_COMMUNICATIONINDICATOR_HPP

#include <QGraphicsPolygonItem>
#include <QPen>

/**
 * A QGraphicsItem showing a communication to be added to a QGraphicsScene
 */
class CommunicationIndicator : public QGraphicsPolygonItem {
public:
    /**
     * Creates a new instance
     * @param from Origin of the communication
     * @param to Target of the communication
     * @param headLength Length of the arrows head in px
     */
    CommunicationIndicator(QPointF from, QPointF to, qreal headLength = 10);

    /**
     * Creates a new instance
     * @param fromX Origin x coordinate of the communication
     * @param fromY Origin y coordinate of the communication
     * @param toX Target x coordinate of the communication
     * @param toY Target y coordinate of the communication
     * @param headLength Length of the arrows head in px
     */
    CommunicationIndicator(qreal fromX, qreal fromY, qreal toX, qreal toY, qreal headLength = 10);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};


#endif //MOTIV_COMMUNICATIONINDICATOR_HPP
