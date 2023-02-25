/*
 * Marvellous OTF2 Traces Interactive Visualizer (MOTIV)
 * Copyright (C) 2023 Florian Gallrein, Björn Gehrke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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

