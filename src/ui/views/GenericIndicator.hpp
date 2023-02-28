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

/**
 * @brief A generic indicator bundling common interaction behaviours.
 *
 * This abstracts handling common interactions such as
 * @tparam T
 * @tparam G
 */
template <class T, class G> requires std::is_base_of_v<QAbstractGraphicsShapeItem, G>
class GenericIndicator : public G {
public: // constructors
    explicit GenericIndicator(T* element, QGraphicsItem *parent = nullptr);

public: // methods
    /**
     * @brief Registers a double click handler
     *
     * Registers a callback function that is invoked whenever the user double clicked on the indicator.
     * @param fn Callback to be invoked on double click
     */
    void setOnDoubleClick(const std::function<void(T *)>& fn);

    /**
     * @brief Registers a select handler
     *
     * Registers a callback function that is invoked whenever the user selects the indicator by left cliking on it.
     * @param fn Callback to be invoked on selection
     */
    void setOnSelected(const std::function<void(T *)>& fn);

protected:
    /**
     * @copydoc QAbstractGraphicsShapeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    /**
     * @copydoc QAbstractGraphicsShapeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    /**
     * @copydoc QAbstractGraphicsShapeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @copydoc QAbstractGraphicsShapeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Checks whether the indicator should react to an event at a given point
     *
     * This function should be overwritten in derived classes. By default this function always returns true.
     *
     * @param point The point at which the event occured
     *
     * @return True if the indicator should react to the event, false otherwise
     */
    virtual bool respondToEvent(QPointF) { return true; };

private:
    T* element_;

private: // event handler
    std::function<void(T*)> onDoubleClick_;
    std::function<void(T *element)>  onSelected_;
};


#endif //MOTIV_GENERICINDICATOR_HPP
