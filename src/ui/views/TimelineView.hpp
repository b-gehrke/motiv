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

class TimelineView : public QGraphicsView {
Q_OBJECT

public:
    explicit TimelineView(TraceDataProxy *data, QWidget *parent = nullptr);

public: Q_SIGNALS:
    void elementSelected(types::TraceTime begin, types::TraceTime end);

public Q_SLOTS:

    void updateView();

protected:
    void resizeEvent(QResizeEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    void populateScene(QGraphicsScene *element);

private:
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINEVIEW_HPP
