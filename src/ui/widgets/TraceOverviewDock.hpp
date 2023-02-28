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
#ifndef MOTIV_TRACEOVERVIEWDOCK_HPP
#define MOTIV_TRACEOVERVIEWDOCK_HPP


#include "src/ui/TraceDataProxy.hpp"
#include "src/ui/views/TimelineView.hpp"
#include "src/ui/views/TraceOverviewTimelineView.hpp"
#include <QDockWidget>

/**
 * @brief A DockWidget holding a TraceOverviewTimelineView
 */
class TraceOverviewDock  : public QDockWidget {
    Q_OBJECT

public:
    /**
     * @brief Creates a new instance of the TraceOverviewDock class
     * @param data The data proxy to obtain the current selection of the trace and to connect to change events
     * @param parent The parent QWidget
     */
    explicit TraceOverviewDock(TraceDataProxy *data, QWidget *parent = nullptr);

private: // data
    TraceDataProxy *data = nullptr;

    TraceOverviewTimelineView *timelineView = nullptr;
    QRubberBand *rubberBand = nullptr;
    QPoint rubberBandOrigin {};
};


#endif //MOTIV_TRACEOVERVIEWDOCK_HPP
