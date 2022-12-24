#include "TraceListView.hpp"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

TraceListView::TraceListView(TraceDataModel *data, QWidget *parent) : data(data) {
    // TODO optionally use OpenGL to speed up rendering
    // setViewport(new QOpenGLWidget(this));
    setAlignment(Qt::AlignTop | Qt::AlignLeft);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    auto scene = new QGraphicsScene(this);
    setScene(scene);

    populateScene(scene);
}

void TraceListView::populateScene(QGraphicsScene *scene) {
    auto selection = data->getSelection();
    auto sceneWidth = width() - 10; // padding at the right
    auto top = 5;

    auto total = data->getEnd() - data->getBegin();

    // Create header
    auto markNum = 4;
    for (size_t i = 0; i < markNum; i++) {
        auto time = (data->getBegin() + static_cast<qreal>(i)/markNum * total) / 1000000000;
        auto textItem = scene->addText(QString::number(time).append('s'));

        // TODO swap 100 for begin of column
        qreal x = 100 + static_cast<qreal>(i)/markNum * sceneWidth;
        qreal y = top;

        textItem->setPos({x, y});
    }
    // TODO font size
    top+=25;

    for (const auto& item : selection->getSlots()) {
        auto location = item.first;

        auto locationNameLabel = scene->addText(QString(location.name().str().c_str()));
        locationNameLabel->setPos({5, static_cast<qreal>(top)});
        locationNameLabel->setToolTip(location.name().str().c_str());

        auto left = 90;
        for (const auto& slot : item.second) {
            auto region_name = slot.region.name().str();
            auto start = slot.start;
            auto end = slot.end;

            auto runtime = static_cast<double>((end - start).count());
            auto rectWidth = runtime/total * sceneWidth;
            rectWidth = qMin(rectWidth, static_cast<double>(sceneWidth - left));

            QRect rect(left, top, qMax(rectWidth, 5.0), 30);
            auto rectItem = scene->addRect(rect);
            rectItem->setToolTip(region_name.c_str());
            rectItem->setZValue(1);

            QColor rectColor;
            if(region_name.starts_with("MPI_")) {
                rectColor = Qt::green;
            } else if(region_name.starts_with("!$omp")) {
                rectColor = Qt::red;
            } else {
                rectColor = Qt::lightGray;
            }

            rectItem->setBrush(rectColor);

            left += rectWidth;
        }

        top += 30;
    }
}

void TraceListView::resizeEvent(QResizeEvent *event) {
    updateView();
    QGraphicsView::resizeEvent(event);
}

void TraceListView::updateView()  {
    // TODO This seems pretty inefficient, no?
    delete scene();
    auto scene = new QGraphicsScene(this);
    // TODO this fucks up the height
    scene->setSceneRect(rect().toRectF());
    populateScene(scene);
    setScene(scene);
}