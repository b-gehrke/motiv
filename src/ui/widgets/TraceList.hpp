#ifndef MOTIV_TRACELIST_HPP
#define MOTIV_TRACELIST_HPP

#include <QWidget>
#include <QScrollArea>
#include "src/models/trace.hpp"
#include "TraceListItem.hpp"


class TraceList : public QScrollArea {
    Q_OBJECT

public:
    TraceList(std::shared_ptr<Trace> tracePtr, QWidget *parent);

Q_SIGNALS:
    void selectionUpdated();

public Q_SLOTS: // slots
    void updateView() { for (auto &item: items) {item->repaint(); item->update(); } };

private: // data
    std::shared_ptr<Trace> trace;
    std::vector<TraceListItem *> items;
};


#endif // MOTIV_TRACELIST_HPP