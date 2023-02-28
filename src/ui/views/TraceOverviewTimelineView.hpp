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
#ifndef MOTIV_TRACEOVERVIEWTIMELINEVIEW_HPP
#define MOTIV_TRACEOVERVIEWTIMELINEVIEW_HPP


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QRubberBand>
#include "src/ui/TraceDataProxy.hpp"
/**
 * @brief A smaller TimelineView dock widget designed for an overview and quick navigation
 *
 * A TraceOverviewTimelineView always shows the entire loaded trace but highlights the current selected time window.
 * Furthermore, it allows selecting a new time range by dragging a selection in the overview.
 */
class TraceOverviewTimelineView : public QGraphicsView {
Q_OBJECT

public:
    /**
     * @brief Creates a new instance of the TraceOverviewTimelineView class.
     * @param fullTrace Pointer to the entire loaded trace
     * @param parent The parent QWidget
     */
    explicit TraceOverviewTimelineView(Trace *fullTrace, QWidget *parent = nullptr);

public: Q_SIGNALS:
    /**
     * @brief Signals a change in the selection
     *
     * This signal should trigger the main view to zoom to the selected time window.
     *
     * @param from The newly selected start time of the selection
     * @param to The newly selected end time of the selection
     */
    void windowSelectionChanged(types::TraceTime from, types::TraceTime to);

public Q_SLOTS:
    /**
     * @brief Updates the view to reflect the current selection of the TraceDataProxy.
     */
    void updateView();

    /**
     * @brief Set a new selection window. The UI is updated to reflect the changes
     * @param from The new start of the selection
     * @param to The new end of the selection
     */
    void setSelectionWindow(types::TraceTime from, types::TraceTime to);


protected:
    /**
     * @copydoc QGraphicsView::mousePressEvent(QMouseEvent*)
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @copydoc QGraphicsView::mouseReleaseEvent(QMouseEvent*)
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /**
     * @copydoc QGraphicsView::mouseMoveEvent(QMouseEvent*)
     */
    void mouseMoveEvent(QMouseEvent *event) override;
    /**
     * @copydoc QGraphicsView::resizeEvent(QResizeEvent*)
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    void populateScene(QGraphicsScene *scene);

private:
    QGraphicsRectItem *selectionRectLeft = nullptr;
    QGraphicsRectItem *selectionRectRight = nullptr;

private:
    Trace *fullTrace = nullptr;
    Trace *uiTrace = nullptr;
    QPoint rubberBandOrigin{};
    QRubberBand *rubberBand = nullptr;
    types::TraceTime selectionFrom;
    types::TraceTime selectionTo;
};



#endif //MOTIV_TRACEOVERVIEWTIMELINEVIEW_HPP
