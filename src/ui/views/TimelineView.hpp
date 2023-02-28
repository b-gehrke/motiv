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
#ifndef MOTIV_TIMELINEVIEW_HPP
#define MOTIV_TIMELINEVIEW_HPP


#include <QGraphicsView>

#include "src/ui/TraceDataProxy.hpp"

/**
 * @brief The main view component rendering the trace
 *
 * This class is the main component responsible for rendering all slots, communications and collective communications.
 * The scene is rerendered whenever the selected time window of the trace changes or the window is resized.
 */
class TimelineView : public QGraphicsView {
Q_OBJECT

public:
    /**
     * @brief Creates a new instance of the TimelineView class.
     *
     * @param data The data proxy to obtain the current selection of the trace and to connect to change events
     * @param parent The parent QWidget
     */
    explicit TimelineView(TraceDataProxy *data, QWidget *parent = nullptr);

public: Q_SIGNALS:
    /**
     * @brief Indicates a TimedElement is selected.
     *
     * @param begin The start time of the selected TimedElement
     * @param end The end time of the selected TimedElement
     */
    void elementSelected(types::TraceTime begin, types::TraceTime end);

public Q_SLOTS:

    /**
     * @brief Updates the view to reflect the current selection of the TraceDataProxy.
     */
    void updateView();

protected:
    /**
     * @copydoc QGraphicsView::resizeEvent(QResizeEvent*)
     */
    void resizeEvent(QResizeEvent *event) override;

    /**
     * @copydoc QGraphicsView::wheelEvent(QWheelEvent*)
     */
    void wheelEvent(QWheelEvent *event) override;

private:
    void populateScene(QGraphicsScene *element);

private:
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINEVIEW_HPP
