#ifndef MOTIV_TRACEOVERVIEWDOCK_HPP
#define MOTIV_TRACEOVERVIEWDOCK_HPP


#include "src/ui/TraceDataProxy.hpp"
#include "src/ui/views/TimelineView.hpp"
#include "src/ui/views/TraceOverviewTimelineView.hpp"
#include <QDockWidget>

class TraceOverviewDock  : public QDockWidget {
    Q_OBJECT

public:
    explicit TraceOverviewDock(TraceDataProxy *data, QWidget *parent = nullptr);

private: // data
    TraceDataProxy *data = nullptr;

    TraceOverviewTimelineView *timelineView = nullptr;
    QRubberBand *rubberBand = nullptr;
    QPoint rubberBandOrigin {};
};


#endif //MOTIV_TRACEOVERVIEWDOCK_HPP
