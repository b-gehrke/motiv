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
