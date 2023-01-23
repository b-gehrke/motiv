#include <QLineF>
#include "CommunicationIndicator.hpp"


CommunicationIndicator::CommunicationIndicator(qreal fromX, qreal fromY, qreal toX, qreal toY, qreal headLength) : CommunicationIndicator(QPointF(fromX, fromY), QPointF(toX, toY), headLength) {

}

CommunicationIndicator::CommunicationIndicator(QPointF from, QPointF to, qreal headLength) : QGraphicsPolygonItem() {
    QPolygonF arrow;
    QLineF line(to, from);

    QLineF headFirst = line.normalVector();
    headFirst.setLength(headLength);
    headFirst.setAngle(headFirst.angle() + 45 + 180);

    auto headSecond = QLineF(headFirst);
    headSecond.setAngle(headSecond.angle() + 90);

    arrow << from << to << headFirst.p2() << to << headSecond.p2() << to;
    setPolygon(arrow);

    setAcceptHoverEvents(true);
}

void CommunicationIndicator::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QPen p(pen());
    p.setWidth(p.width() * 2);
    setPen(p);

    setZValue(zValue() + 10);

    QGraphicsItem::hoverEnterEvent(event);
}

void CommunicationIndicator::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QPen p(pen());
    p.setWidth(p.width() / 2);
    setPen(p);

    setZValue(zValue() - 10);

    QGraphicsItem::hoverLeaveEvent(event);
}

