#ifndef MOTIV_TRACELIST_HPP
#define MOTIV_TRACELIST_HPP

#include <QWidget>
#include <QScrollArea>
#include "src/models/trace.hpp"

namespace view {

class TraceList : public QScrollArea {
    Q_OBJECT
public:
    TraceList(QWidget *parent, std::shared_ptr<Trace>);

private:
    std::shared_ptr<Trace> trace;
};

} // namespace view

#endif // MOTIV_TRACELIST_HPP