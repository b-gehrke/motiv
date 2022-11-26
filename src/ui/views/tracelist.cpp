#include "tracelist.hpp"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <utility>

using namespace view;

TraceList::TraceList(std::shared_ptr<Trace> tracePtr, QWidget *parent)
: trace(std::move(tracePtr)) {
    // TODO qgraphicsview?
    auto widget = new QWidget(this);
    auto vLayout = new QVBoxLayout(this);

    widget->setLayout(vLayout);
    setWidget(widget);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    for(int i = 0; i < 100; i++) {
//        auto label = new QLabel(QString::number(i), this);
//        vLayout->addWidget(label);
//    }
}