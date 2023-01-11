#include "TimelineLabelList.hpp"

#include <QLabel>
#include <QVBoxLayout>

TimelineLabelList::TimelineLabelList(TraceDataProxy *data, QWidget *parent) : QWidget(parent), data(data) {
    auto layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    for (const auto &ranks : this->data->getSelection()->getSlots()) {
        const auto &rankName = ranks.first->name().str();
        auto label = new QLabel(QString::fromStdString(rankName), this);
        layout->addWidget(label);
    }
}
