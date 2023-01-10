#include "TimelineHeader.hpp"
#include "TimeUnitLabel.hpp"

#include <QHBoxLayout>
#include <QLabel>

TimelineHeader::TimelineHeader(TraceDataProxy *data, QWidget *parent) : QWidget(parent), data(data) {
    auto layout = new QHBoxLayout(this);

    auto selection = this->data->getSelection();
    auto runtime = static_cast<double>(selection->getRuntime().count());
    auto begin = static_cast<double>(selection->getStartTime().count());

    int marks = 4;
    for (int i = 0; i <= marks; i++) {
        double num = begin + static_cast<double>(i)/marks * runtime;
        auto label = new TimeUnitLabel(num, this);
        layout->addWidget(label);
    }
}
