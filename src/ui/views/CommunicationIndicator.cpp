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
