#ifndef MOTIV_PREVIEW_HPP
#define MOTIV_PREVIEW_HPP

#include "src/models/filetrace.hpp"

#include <QGraphicsView>
#include <QWidget>

namespace view {

class Preview : public QGraphicsView {
    Q_OBJECT

public:
    Preview(QWidget *parent, FileTrace *trace);

private:
    QGraphicsScene *scene;
};

} // namespace view

#endif // MOTIV_PREVIEW_HPP