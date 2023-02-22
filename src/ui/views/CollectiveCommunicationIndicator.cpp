#include "CollectiveCommunicationIndicator.hpp"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

CollectiveCommunicationIndicator::CollectiveCommunicationIndicator(CollectiveCommunicationEvent *element,
                                                                   QGraphicsItem *parent)
    : GenericIndicator(element, parent) {
    setAcceptHoverEvents(false);
}

bool CollectiveCommunicationIndicator::respondToEvent(QPointF mousePos) {
    // Only react to events if this indicator is not covering something.
    // Otherwise, MPI events within the time range of the collective event are covered and mouse events are not forwarded to
    // the respective indicators
    return scene()->items(mousePos).length() == 1;
}

