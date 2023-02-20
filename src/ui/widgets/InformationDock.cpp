#include "TimeUnitLabel.hpp"
#include "src/utils.hpp"
#include <QPushButton>
#include <QFormLayout>
#include "InformationDock.hpp"



InformationDock::InformationDock(QWidget *parent) : QDockWidget(parent) {
    setWindowTitle(tr("Details"));
}

void InformationDock::updateView() {
    if(!element_) return;

    QWidget* newWidget = nullptr;
    for (auto &item: strategies_) {
        auto widget = item.first;
        auto strategy = item.second;
        if(strategy->update(static_cast<QFormLayout *>(widget->layout()), element_)) {
            newWidget = widget;
            break;
        }
    }

    if(newWidget) {
        setWidget(newWidget);
    }
}

void InformationDock::zoomIntoViewPressed() {
    if(!element_) return;

    auto padding = element_->getDuration() / 10;

    Q_EMIT zoomToWindow(element_->getStartTime() - padding, element_->getEndTime() + padding);
}

void InformationDock::setElement(TimedElement *element) {
    element_ = element;

    updateView();
}

void InformationDock::addElementStrategy(InformationDockElementStrategy* s) {
    auto widget = new QWidget();
    auto layout = new QFormLayout(widget);
    layout->setAlignment(Qt::AlignLeading | Qt::AlignTop);

    s->setup(layout);

    auto zoomIntoViewButton = new QPushButton(tr("Zoom into &view"));
    connect(zoomIntoViewButton, SIGNAL(clicked()), this, SLOT(zoomIntoViewPressed()));
    layout->addWidget(zoomIntoViewButton);

    widget->setLayout(layout);

    strategies_.emplace_back(widget, s);
}
