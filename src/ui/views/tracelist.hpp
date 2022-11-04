#ifndef MOTIV_TRACELIST_HPP
#define MOTIV_TRACELIST_HPP

#include <QWidget>

namespace view {

class TraceList : public QWidget {
    Q_OBJECT
public:
    TraceList(QWidget *parent);
};

} // namespace view

#endif // MOTIV_TRACELIST_HPP