#include "traceoverview.hpp"

#include <QFrame>

using namespace view;

TraceOverview::TraceOverview(QWidget *parent) {
    auto frame = new QFrame(this);
    frame->setFrameStyle(QFrame::Shadow::Plain | QFrame::Shape::Box);
}