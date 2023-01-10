#ifndef MOTIV_TIMELINEHEADER_HPP
#define MOTIV_TIMELINEHEADER_HPP


#include <QWidget>

#include "TraceDataProxy.hpp"

class TimelineHeader : public QWidget {
    Q_OBJECT

public:
    TimelineHeader(TraceDataProxy *data, QWidget *parent = nullptr);

private:
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINEHEADER_HPP
