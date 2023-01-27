#ifndef MOTIV_TRACETREEVIEW_HPP
#define MOTIV_TRACETREEVIEW_HPP


#include <QWidget>
#include <QDockWidget>
#include "src/models/TraceTree.hpp"

class TraceTreeView  : public QDockWidget {
    Q_OBJECT

public:
    explicit TraceTreeView(QWidget *parent = nullptr);

public: Q_SIGNALS:

    void setTree(TraceTree *t);

public Q_SLOTS:

protected:
    void updateView();

private: // fields
    TraceTree *tree = nullptr;

private: // widgets
    QTreeView *child = nullptr;
};


#endif //MOTIV_TRACETREEVIEW_HPP
