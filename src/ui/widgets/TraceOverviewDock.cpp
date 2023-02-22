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
