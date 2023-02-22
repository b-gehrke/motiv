#ifndef MOTIV_TIMELINEVIEW_HPP
#define MOTIV_TIMELINEVIEW_HPP


#include <QGraphicsView>

#include "src/ui/TraceDataProxy.hpp"

class TimelineView : public QGraphicsView {
Q_OBJECT

public:
    explicit TimelineView(TraceDataProxy *data, QWidget *parent = nullptr);

public: Q_SIGNALS:
    void elementSelected(types::TraceTime begin, types::TraceTime end);

public Q_SLOTS:

    void updateView();

protected:
    void resizeEvent(QResizeEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    void populateScene(QGraphicsScene *element);

private:
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINEVIEW_HPP
