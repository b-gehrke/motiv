#ifndef MOTIV_TIMELINE_HPP
#define MOTIV_TIMELINE_HPP


#include <QWidget>

#include "TimelineHeader.hpp"
#include "TimelineLabelList.hpp"
#include "TimelineView.hpp"
#include "TraceDataProxy.hpp"

class Timeline : public QWidget {
    Q_OBJECT

public:
    explicit Timeline(TraceDataProxy *data, QWidget *parent = nullptr);

private: // widgets
    TimelineHeader *header = nullptr;
    TimelineLabelList *labelList = nullptr;
    TimelineView *view = nullptr;

private: // data
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINE_HPP
