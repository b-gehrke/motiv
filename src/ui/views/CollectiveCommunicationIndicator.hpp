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
#ifndef MOTIV_COLLECTIVECOMMUNICATIONINDICATOR_HPP
#define MOTIV_COLLECTIVECOMMUNICATIONINDICATOR_HPP


#include <QGraphicsRectItem>
#include "src/models/communication/CollectiveCommunicationEvent.hpp"
#include "GenericIndicator.hpp"

/**
 * @brief Indicator for collective communications
 *
 * A collective communication is indicated by a rectangle. It only reacts to click events, if there are no other elements
 * drawn behind it to avoid confusion when clicking on slots within a collective communication. For the same reasons, it
 * does not highlight when hovering over it.
 */
class CollectiveCommunicationIndicator : public GenericIndicator<CollectiveCommunicationEvent, QGraphicsRectItem> {
public:
    /**
     * @brief Creates a new instance of the CollectiveCommunicationIdicator class
     * @param element The CollectiveCommunicationEvent object the indicator is representing
     * @param parent The parent QGraphicsItem
     */
    explicit CollectiveCommunicationIndicator(CollectiveCommunicationEvent *element, QGraphicsItem *parent = nullptr);

protected:
    /**
     * @copydoc GenericIndicator::respondToEvent(QPointF);
     */
    bool respondToEvent(QPointF mousePos) override;
};


#endif //MOTIV_COLLECTIVECOMMUNICATIONINDICATOR_HPP
