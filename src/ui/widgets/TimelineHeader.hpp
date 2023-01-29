#ifndef MOTIV_TIMELINEHEADER_HPP
#define MOTIV_TIMELINEHEADER_HPP


#include <QWidget>

#include "src/ui/TraceDataProxy.hpp"

class TimelineHeader : public QWidget {
    Q_OBJECT

public:
    TimelineHeader(TraceDataProxy *data, QWidget *parent = nullptr);

public Q_SLOTS:
    void updateView();

private: // widgets
    std::vector<QWidget *> labels;

private: // data
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINEHEADER_HPP
