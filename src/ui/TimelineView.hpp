#ifndef MOTIV_TIMELINEVIEW_HPP
#define MOTIV_TIMELINEVIEW_HPP


#include <QGraphicsView>

#include "TraceDataProxy.hpp"

class TimelineView : public QGraphicsView {
    Q_OBJECT

public:
    TimelineView(TraceDataProxy *data, QWidget *parent = nullptr);

private:
    void populateScene();

private:
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINEVIEW_HPP
