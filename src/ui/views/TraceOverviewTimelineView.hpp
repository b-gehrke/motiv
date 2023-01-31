#ifndef MOTIV_TRACEOVERVIEWTIMELINEVIEW_HPP
#define MOTIV_TRACEOVERVIEWTIMELINEVIEW_HPP


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QRubberBand>
#include "src/ui/TraceDataProxy.hpp"

class TraceOverviewTimelineView : public QGraphicsView {
Q_OBJECT

public:
    explicit TraceOverviewTimelineView(Trace *fullTrace, QWidget *parent = nullptr);

public: Q_SIGNALS:
    void windowSelectionChanged(types::TraceTime from, types::TraceTime to);

public Q_SLOTS:
    void updateView();
    void setSelectionWindow(types::TraceTime from, types::TraceTime to);


protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void populateScene(QGraphicsScene *scene);

private:
    QGraphicsRectItem *selectionRectLeft = nullptr;
    QGraphicsRectItem *selectionRectRight = nullptr;

private:
    Trace *fullTrace = nullptr;
    Trace *uiTrace = nullptr;
    QPoint rubberBandOrigin{};
    QRubberBand *rubberBand = nullptr;
};



#endif //MOTIV_TRACEOVERVIEWTIMELINEVIEW_HPP
