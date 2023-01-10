#include "TimelineHeader.hpp"
#include "TimeUnitLabel.hpp"

#include <QHBoxLayout>
#include <QLabel>

TimelineHeader::TimelineHeader(TraceDataProxy *data, QWidget *parent) : QWidget(parent), data(data) {
    this->setLayout(new QHBoxLayout(this));
    this->updateView();

    connect(this->data, SIGNAL(selectionChanged()), this, SLOT(updateView()));
}

void TimelineHeader::updateView() {
    auto layout = this->layout();
    auto selection = this->data->getSelection();
    auto runtime = static_cast<double>(selection->getRuntime().count());
    auto begin = static_cast<double>(selection->getStartTime().count());

    for (const auto &widget : this->labels) {
        layout->removeWidget(widget);
        delete widget;
    }
    this->labels.clear();

    int marks = 4;
    for (int i = 0; i <= marks; i++) {
        double num = begin + static_cast<double>(i)/marks * runtime;
        auto label = new TimeUnitLabel(num, this);
        this->labels.push_back(label);
        layout->addWidget(label);
    }
}
