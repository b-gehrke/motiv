/*
 * Marvelous OTF2 Traces Interactive Visualizer (MOTIV)
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
#include <QLineF>
#include "CommunicationIndicator.hpp"
#include "src/ui/Constants.hpp"


CommunicationIndicator::CommunicationIndicator(Communication *communication, qreal fromX, qreal fromY, qreal toX, qreal toY, qreal headLength)
    : CommunicationIndicator(communication, QPointF(fromX, fromY), QPointF(toX, toY), headLength) {

}

CommunicationIndicator::CommunicationIndicator(Communication *communication, QPointF from, QPointF to, qreal headLength)
    : GenericIndicator<Communication, QGraphicsPolygonItem>(communication) {
    QPolygonF arrow;
    QLineF line(to, from);

    QLineF headFirst = line.normalVector();
    headFirst.setLength(headLength);
    headFirst.setAngle(headFirst.angle() + 45 + 180);

    auto headSecond = QLineF(headFirst);
    headSecond.setAngle(headSecond.angle() + 90);

    arrow << from << to << headFirst.p2() << to << headSecond.p2() << to;
    setPolygon(arrow);
}
