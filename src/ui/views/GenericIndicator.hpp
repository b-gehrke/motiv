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
#ifndef MOTIV_GENERICINDICATOR_HPP
#define MOTIV_GENERICINDICATOR_HPP


#include <QGraphicsItem>

template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
class GenericIndicator : public G {
public: // constructors
    explicit GenericIndicator(T* element, QGraphicsItem *parent = nullptr);

public: // methods
    void setOnDoubleClick(const std::function<void(T *)>& fn);
    void setOnSelected(const std::function<void(T *)>& fn);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    virtual bool respondToEvent(QPointF) { return true; };

private:
    T* element_;

private: // event handler
    std::function<void(T*)> onDoubleClick_;
    std::function<void(T *element)>  onSelected_;
};


#endif //MOTIV_GENERICINDICATOR_HPP
