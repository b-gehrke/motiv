#ifndef MOTIV_TRACELIST_HPP
#define MOTIV_TRACELIST_HPP

#include <QWidget>
#include <QScrollArea>
#include "src/models/trace.hpp"

namespace view {

class TraceList : public QScrollArea {
    Q_OBJECT

public:
    TraceList(std::shared_ptr<Trace> tracePtr, QWidget *parent);

public: // slots
    void updateView(otf2::chrono::duration start, otf2::chrono::duration end);

private: // data
    std::shared_ptr<Trace> trace;
};

} // namespace view

#endif // MOTIV_TRACELIST_HPP