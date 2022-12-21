//
// Created by Florian Gallrein on 19.12.22.
//

#include "TraceListView.hpp"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

TraceListView::TraceListView(TraceDataModel *data, QWidget *parent) {
    // TODO optionally use OpenGL to speed up rendering
    // setViewport(new QOpenGLWidget(this));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    auto scene = new QGraphicsScene(this);
    setScene(scene);

    auto selection = data->getSelection();
    auto top = 0;
    for (const auto& item : selection->getSlots()) {
        auto location = item.first;

        auto locationNameLabel = scene->addText(QString(location.name().str().c_str()));
        locationNameLabel->setPos({20, static_cast<qreal>(top) + 40});

        auto total = static_cast<double>(((--item.second.end())->end - item.second.begin()->start).count());

        auto left = 100;
        for (const auto& slot : item.second) {
            auto region_name = slot.region.name().str();
            auto start = slot.start;
            auto end = slot.end;

            auto runtime = static_cast<double>((end - start).count());
            auto rectWidth = qFloor(runtime/total * width());

            QRect rect(left, top, rectWidth, 90);
            auto rectItem = scene->addRect(rect);
            rectItem->setToolTip(region_name.c_str());

            QColor rectColor;
            if(region_name.starts_with("MPI_"))
                rectColor = Qt::green;
            else if(region_name.starts_with("!$omp"))
                rectColor = Qt::red;
            else
                rectColor = Qt::lightGray;

            rectItem->setBrush(rectColor);

            left += rectWidth;
        }

        top += 100;
    }
}
