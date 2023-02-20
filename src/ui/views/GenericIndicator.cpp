#include "GenericIndicator.hpp"

#include <QPen>
#include <QGraphicsSceneMouseEvent>

#include "src/models/communication/Communication.hpp"
#include "src/models/Slot.hpp"
#include "src/ui/Constants.hpp"
#include "src/models/communication/CollectiveCommunicationEvent.hpp"

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
GenericIndicator<T, G>::GenericIndicator(T *element, QGraphicsItem *parent)
    : element_(element), G() {
    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::setOnDoubleClick(const std::function<void(T *)>& fn) {
    onDoubleClick = fn;
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::setOnSelected(const std::function<void(T *)>& fn) {
    onSelected = fn;
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (onDoubleClick && respondToEvent(event->pos())) {
        onDoubleClick(element_);
        event->accept();
    } else {
        G::mouseDoubleClickEvent(event);
    }
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (onSelected && respondToEvent(event->pos())) {
        onSelected(element_);
        event->accept();
    } else {
        G::mousePressEvent(event);
    }
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    if(!highlightOnHover) return;

    QPen p(G::pen());
    p.setWidth(p.width() * 2);
    G::setPen(p);

    G::setZValue(G::zValue() + layers::Z_LAYER_HIGHLIGHTED_OFFSET);

    QGraphicsItem::hoverEnterEvent(event);
}

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    if(!highlightOnHover) return;

    QPen p(G::pen());
    p.setWidth(p.width() / 2);
    G::setPen(p);

    G::setZValue(G::zValue() - layers::Z_LAYER_HIGHLIGHTED_OFFSET);

    QGraphicsItem::hoverLeaveEvent(event);
}

template<class T, class G>
requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
void GenericIndicator<T, G>::setHighlightOnHover(const bool val) {
    highlightOnHover = val;
}

template class GenericIndicator<Communication, QGraphicsPolygonItem>;
template class GenericIndicator<Slot, QGraphicsRectItem>;
template class GenericIndicator<CollectiveCommunicationEvent, QGraphicsRectItem>;
