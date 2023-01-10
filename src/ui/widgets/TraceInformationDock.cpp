#include <QGridLayout>
#include <QLabel>
#include "TraceInformationDock.hpp"


TraceInformationDock::TraceInformationDock(std::shared_ptr<Trace> tracePtr, QWidget *parent) : QDockWidget(tr("Trace Information"), parent), trace(std::move(tracePtr)) {
    auto runtime = trace->getRuntime().count();

    auto child = new QWidget(this);
    setWidget(child);
    auto layout = new QGridLayout(child);
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(new QLabel(tr("Path:"), this), 0, 0);
//    layout->addWidget(new QLabel(parent->filePath, this), 0, 1);

    layout->addWidget(new QLabel(tr("Runtime:"), this), 1, 0);
    layout->addWidget(new QLabel(QString::number(runtime), this), 1, 1);

    child->setLayout(layout);
}