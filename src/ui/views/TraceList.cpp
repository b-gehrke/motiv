#include "TraceList.hpp"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsView>
#include <set>

using namespace view;

TraceList::TraceList(std::shared_ptr<Trace> tracePtr, QWidget *parent)
: trace(std::move(tracePtr)) {
    auto widget = new QWidget(this);
    auto layout = new QGridLayout(widget);
    layout->setAlignment(Qt::AlignTop);

    widget->setLayout(layout);
    setWidget(widget);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    std::set<std::string> set;
    for (const auto& slot : trace->getSlots()) {
        auto locationName = slot.location.location_group().name().str();
        set.insert(locationName);

//        auto label = new QLabel(QString::fromStdString(slot.region.name().str()), widget);
//        layout->addWidget(label);
    }

    int i = 0;
    // TODO ordered lexicographically :(
    for (const auto& name : set) {
        auto label = new QLabel(QString::fromStdString(name), widget);
        layout->addWidget(label, i, 0);
        ++i;
    }
}