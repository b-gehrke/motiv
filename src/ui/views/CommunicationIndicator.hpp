#ifndef MOTIV_COMMUNICATIONINDICATOR_HPP
#define MOTIV_COMMUNICATIONINDICATOR_HPP

#include <QGraphicsPolygonItem>
#include <QPen>
#include "GenericIndicator.hpp"
#include "src/models/communication/Communication.hpp"

/**
 * A QGraphicsItem showing a communication to be added to a QGraphicsScene
 */
class CommunicationIndicator : public GenericIndicator<Communication, QGraphicsPolygonItem>{
public:
    /**
     * Creates a new instance
     * @param communication The represented communication
     * @param from Origin of the communication
     * @param to Target of the communication
     * @param headLength Length of the arrows head in px
     */
    CommunicationIndicator(Communication *communication, QPointF from, QPointF to, qreal headLength = 10);

    /**
     * Creates a new instance
     * @param communication The represented communication
     * @param fromX Origin x coordinate of the communication
     * @param fromY Origin y coordinate of the communication
     * @param toX Target x coordinate of the communication
     * @param toY Target y coordinate of the communication
     * @param headLength Length of the arrows head in px
     */
    CommunicationIndicator(Communication *communication, qreal fromX, qreal fromY, qreal toX, qreal toY, qreal headLength = 10);
};


#endif //MOTIV_COMMUNICATIONINDICATOR_HPP
