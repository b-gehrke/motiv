#include "TimelineLabelList.hpp"

#include <QLabel>
#include <QVBoxLayout>

TimelineLabelList::TimelineLabelList(QWidget *parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);

    for (int i = 0; i < 4; i++) {
        auto label = new QLabel(QString::number(i), this);
        // TODO set size
        layout->addWidget(label);
        layout->setAlignment(Qt::AlignTop);
    }
}
