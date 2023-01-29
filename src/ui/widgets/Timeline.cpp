#include "Timeline.hpp"
#include "src/ui/ScrollSynchronizer.hpp"

#include <QGridLayout>

Timeline::Timeline(TraceDataProxy *data, QWidget *parent) : QWidget(parent), data(data) {
    auto layout = new QGridLayout(this);

    this->header = new TimelineHeader(this->data, this);
    layout->addWidget(this->header, 0, 1);

    this->labelList = new TimelineLabelList(this->data, this);
    layout->addWidget(this->labelList, 1, 0);

    this->view = new TimelineView(this->data, this);
    layout->addWidget(this->view, 1, 1);

    // This prevents the labelList from expanding to 50% of the width.
    // Not really a satisfactory solution.
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 9);

    auto scrollSyncer = new ScrollSynchronizer(this);
    scrollSyncer->addWidget(this->labelList);
    scrollSyncer->addWidget(this->view);
}
