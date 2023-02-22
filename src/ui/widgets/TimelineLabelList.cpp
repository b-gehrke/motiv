#include "TimelineLabelList.hpp"

#include <QLabel>
#include <QSizePolicy>
#include <QVBoxLayout>

TimelineLabelList::TimelineLabelList(TraceDataProxy *data, QWidget *parent) : QListWidget(parent), data(data) {
    this->setFrameShape(QFrame::NoFrame);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet("background: transparent");
    setViewportMargins(0, 20, 0, 0);

    for (const auto &ranks: this->data->getSelection()->getSlots()) {
        const auto &rankName = ranks.first->name().str();
        auto item = new QListWidgetItem(this);
        item->setText(QString::fromStdString(rankName));
        item->setSizeHint(QSize(0, 30 /* TODO ROW_HEIGHT */));
        item->setTextAlignment(Qt::AlignCenter);
        this->addItem(item);
    }
}

void TimelineLabelList::mousePressEvent(QMouseEvent *) {
    return;
}

void TimelineLabelList::mouseReleaseEvent(QMouseEvent *) {
    return;
}

void TimelineLabelList::mouseMoveEvent(QMouseEvent *) {
    return;
}
