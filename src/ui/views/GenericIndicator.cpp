#include "GenericIndicator.hpp"

#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "src/models/communication/Communication.hpp"
#include "src/models/Slot.hpp"
#include "src/ui/Constants.hpp"
#include "src/models/communication/CollectiveCommunicationEvent.hpp"

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
GenericIndicator<T, G>::GenericIndicator(T *element, QGraphicsItem *)
    : G(), element_(element) {
    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::setOnDoubleClick(const std::function<void(T *)>& fn) {
    onDoubleClick_ = fn;
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::setOnSelected(const std::function<void(T *)>& fn) {
    onSelected_ = fn;
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (onDoubleClick_ && respondToEvent(event->pos())) {
        onDoubleClick_(element_);
        event->accept();
    } else {
        G::mouseDoubleClickEvent(event);
    }
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (onSelected_ && respondToEvent(event->pos())) {
        onSelected_(element_);
        event->accept();
    } else {
        G::mousePressEvent(event);
    }
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QPen p(G::pen());
    p.setWidth(p.width() * 2);
    G::setPen(p);

    G::setZValue(G::zValue() + layers::Z_LAYER_HIGHLIGHTED_OFFSET);

    QGraphicsItem::hoverEnterEvent(event);
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QPen p(G::pen());
    p.setWidth(p.width() / 2);
    G::setPen(p);

    G::setZValue(G::zValue() - layers::Z_LAYER_HIGHLIGHTED_OFFSET);

    QGraphicsItem::hoverLeaveEvent(event);
}

template class GenericIndicator<Communication, QGraphicsPolygonItem>;
template class GenericIndicator<Slot, QGraphicsRectItem>;
template class GenericIndicator<CollectiveCommunicationEvent, QGraphicsRectItem>;
