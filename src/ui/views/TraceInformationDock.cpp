#include <QGridLayout>
#include <QLabel>
#include "TraceInformationDock.hpp"

using namespace view;

TraceInformationDock::TraceInformationDock(std::shared_ptr<Trace> tracePtr, QWidget *parent) : QDockWidget(tr("Trace Information"), parent), trace(std::move(tracePtr)) {
    auto runtime = trace->getRuntime().count();

    auto child = new QWidget(this);
    setWidget(child);
    auto layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(new QLabel(tr("Runtime:"), this), 0, 0);
    layout->addWidget(new QLabel(QString::number(runtime), this), 0, 1);
    child->setLayout(layout);
}