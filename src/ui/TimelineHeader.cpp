#include "TimelineHeader.hpp"

#include <QHBoxLayout>
#include <QLabel>

#include "TimeUnitLabel.hpp"
#include "src/utils.hpp"

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

    resetLayout(layout);

    int marks = 4;
    for (int i = 0; i <= marks; i++) {
        double num = begin + static_cast<double>(i)/marks * runtime;
        auto label = new TimeUnitLabel(num, this);
        layout->addWidget(label);
        if (i != marks) {
            dynamic_cast<QHBoxLayout *>(layout)->addStretch();
        }
    }
}
