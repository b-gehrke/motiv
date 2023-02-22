#ifndef MOTIV_COLLECTIVECOMMUNICATIONINDICATOR_HPP
#define MOTIV_COLLECTIVECOMMUNICATIONINDICATOR_HPP


#include <QGraphicsRectItem>
#include "src/models/communication/CollectiveCommunicationEvent.hpp"
#include "GenericIndicator.hpp"

class CollectiveCommunicationIndicator : public GenericIndicator<CollectiveCommunicationEvent, QGraphicsRectItem> {
public:
    CollectiveCommunicationIndicator(CollectiveCommunicationEvent *element, QGraphicsItem *parent = nullptr);

protected:
    bool respondToEvent(QPointF mousePos) override;
};


#endif //MOTIV_COLLECTIVECOMMUNICATIONINDICATOR_HPP
