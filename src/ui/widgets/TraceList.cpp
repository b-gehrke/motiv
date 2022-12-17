#include "TraceList.hpp"
#include "TraceListItem.hpp"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsView>
#include <set>


TraceList::TraceList(std::shared_ptr<Trace> tracePtr, QWidget *parent)
: trace(std::move(tracePtr)), items() {
    auto widget = new QWidget(this);
    auto layout = new QGridLayout(widget);
    layout->setAlignment(Qt::AlignTop);

    widget->setLayout(layout);
    setWidget(widget);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    for (const auto& slot : trace->getSlots()) {
        auto item = new TraceListItem(QString::fromStdString(slot.first.name().str()), slot.second, trace->getStartTime().count(), trace->getRuntime().count(), this);
        layout->addWidget(item);
        items.push_back(item);
    }
}