#include "TimelineView.hpp"

TimelineView::TimelineView(QWidget *parent) : QGraphicsView(parent) {
    auto scene = new QGraphicsScene(this);
    this->setAutoFillBackground(false);
    this->setScene(scene);
}
