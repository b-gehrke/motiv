#ifndef MOTIV_TIMELINELABELLIST_HPP
#define MOTIV_TIMELINELABELLIST_HPP


#include <QWidget>
#include "TraceDataProxy.hpp"

class TimelineLabelList : public QWidget {
    Q_OBJECT

public:
    TimelineLabelList(TraceDataProxy *data, QWidget *parent = nullptr);

private:
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINELABELLIST_HPP
