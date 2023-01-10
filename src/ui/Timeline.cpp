#include "Timeline.hpp"

#include <QGridLayout>

Timeline::Timeline(TraceDataProxy *data, QWidget *parent) : QWidget(parent), data(data) {
    auto layout = new QGridLayout(this);

    this->header = new TimelineHeader(this->data, this);
    layout->addWidget(this->header, 0, 1);

    this->labelList = new TimelineLabelList(this);
    layout->addWidget(this->labelList, 1, 0);

    this->view = new TimelineView(this->data, this);
    layout->addWidget(this->view, 1, 1);
}
