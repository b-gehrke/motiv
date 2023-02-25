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
#ifndef MOTIV_TRACEOVERVIEWTIMELINEVIEW_HPP
#define MOTIV_TRACEOVERVIEWTIMELINEVIEW_HPP


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QRubberBand>
#include "src/ui/TraceDataProxy.hpp"

class TraceOverviewTimelineView : public QGraphicsView {
Q_OBJECT

public:
    explicit TraceOverviewTimelineView(Trace *fullTrace, QWidget *parent = nullptr);

public: Q_SIGNALS:
    void windowSelectionChanged(types::TraceTime from, types::TraceTime to);

public Q_SLOTS:
    void updateView();
    void setSelectionWindow(types::TraceTime from, types::TraceTime to);


protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
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
