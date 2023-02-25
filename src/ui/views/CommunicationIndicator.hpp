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
