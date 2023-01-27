#include <QTreeView>
#include "TraceTreeView.hpp"

TraceTreeView::TraceTreeView(QWidget *parent) : QDockWidget(parent) {
    child = new QTreeView();


    setWidget(child);
    setWindowTitle(tr("Details"));
}

void TraceTreeView::setTree(TraceTree *t) {
    TraceTreeView::tree = t;

    updateView();
}

void TraceTreeView::updateView() {
    child->setModel()
}
