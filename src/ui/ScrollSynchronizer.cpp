#include "ScrollSynchronizer.hpp"

#include <QScrollBar>

ScrollSynchronizer::ScrollSynchronizer(QObject *parent) : QObject(parent) {

}

void ScrollSynchronizer::addWidget(QAbstractScrollArea *newWidget) {
    if (this->widgets.contains(newWidget)) {
        return;
    }
    for (const auto &widget : this->widgets) {
        connect(widget->verticalScrollBar(), &QScrollBar::valueChanged, newWidget->verticalScrollBar(), &QScrollBar::setValue);
        connect(newWidget->verticalScrollBar(), &QScrollBar::valueChanged, widget->verticalScrollBar(), &QScrollBar::setValue);
    }
    this->widgets.push_back(newWidget);
}
