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
#include <QRubberBand>
#include "TraceOverviewDock.hpp"
#include "src/ui/views/TimelineView.hpp"
#include "src/ui/views/TraceOverviewTimelineView.hpp"

TraceOverviewDock::TraceOverviewDock(TraceDataProxy *data, QWidget *parent) : QDockWidget(parent), data(data) {
    timelineView = new TraceOverviewTimelineView(data->getFullTrace());

    setWidget(timelineView);

    connect(data, SIGNAL(selectionChanged(types::TraceTime,types::TraceTime)), timelineView, SLOT(setSelectionWindow(types::TraceTime,types::TraceTime)));
    connect(timelineView, SIGNAL(windowSelectionChanged(types::TraceTime,types::TraceTime)), data, SLOT(setSelection(types::TraceTime,types::TraceTime)));
}
