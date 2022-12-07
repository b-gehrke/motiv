#ifndef MOTIV_TRACELISTITEM_HPP
#define MOTIV_TRACELISTITEM_HPP

#include <QWidget>
#include "src/models/slot.hpp"
#include "src/models/trace.hpp"

namespace view {

    class TraceListItem : public QWidget {
    public:
        explicit TraceListItem(const QString &name, const Range<Slot> &slots, const QWidget &parent);
    };

} // view

#endif //MOTIV_TRACELISTITEM_HPP
