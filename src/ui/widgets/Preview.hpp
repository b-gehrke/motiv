#ifndef MOTIV_PREVIEW_HPP
#define MOTIV_PREVIEW_HPP

#include "src/models/filetrace.hpp"

#include <QGraphicsView>
#include <QWidget>


class Preview : public QGraphicsView {
    Q_OBJECT

public:
    Preview(std::shared_ptr<Trace> trace, QWidget *parent);

public: // slots
    void updateView(otf2::chrono::duration start, otf2::chrono::duration end);

private: // Qt
    QGraphicsScene *scene = nullptr;

private: // data
    std::shared_ptr<Trace> trace = nullptr;
};


#endif // MOTIV_PREVIEW_HPP