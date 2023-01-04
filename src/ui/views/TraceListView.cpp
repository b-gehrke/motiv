#include "TraceListView.hpp"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

static const int X_AXIS_HEIGHT = 30;
static const int Y_AXIS_WIDTH = 100;
static const int LEADING_MARGIN = 5;
static const int TRAILING_MARGIN = 5;
static const int TOP_MARGIN = 5;
static const int BOTTOM_MARGIN = 5;
static const int ROW_HEIGHT = 30;

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
    auto sceneWidth = width() - LEADING_MARGIN - Y_AXIS_WIDTH - TRAILING_MARGIN;

    auto selectionBegin = data->getBegin();
    auto selectionEnd = data->getEnd();
    auto selectionRuntime = selectionEnd - selectionBegin;

    // Create header/x-axis
    auto markerCount = 4;
    for (size_t i = 0; i < markerCount; i++) {
        auto time = (static_cast<qreal>(data->getBegin())
                + (static_cast<qreal>(i) / markerCount) * static_cast<qreal>(selectionRuntime)) / 1000000000;
        auto textItem = scene->addText(QString::number(time).append('s'));

        qreal x = (TRAILING_MARGIN + Y_AXIS_WIDTH) + static_cast<qreal>(i) / markerCount * sceneWidth;
        qreal y = TOP_MARGIN;

        textItem->setPos({x, y});
        // TODO set font size or make header height variable
    }

    // Create rows
    auto top = TOP_MARGIN + X_AXIS_HEIGHT;
    for (const auto& item : selection->getSlots()) {
        auto location = item.first;

        // Display name at the beginning of a row
        auto locationNameLabel = scene->addText(QString(location.name().str().c_str()));
        locationNameLabel->setPos({LEADING_MARGIN, static_cast<qreal>(top)});
        locationNameLabel->setToolTip(location.name().str().c_str());

        // Display slots
        for (const auto& slot : item.second) {
            auto region_name = slot.region.name().str();
            auto startTime = slot.start;
            auto endTime = slot.end;

            auto slotBeginPos = (LEADING_MARGIN + Y_AXIS_WIDTH)
                    + (static_cast<qreal>(startTime.count() - selectionBegin) / static_cast<qreal>(selectionRuntime)) * sceneWidth;

            auto slotRuntime = static_cast<qreal>((endTime - startTime).count());
            auto rectWidth = (slotRuntime / static_cast<qreal>(selectionRuntime)) * sceneWidth;
            rectWidth = qMin(rectWidth, static_cast<qreal>(sceneWidth - slotBeginPos - 1));

            QRectF rect(slotBeginPos, top, qMax(rectWidth, 5.0), ROW_HEIGHT);
            auto rectItem = scene->addRect(rect);
            rectItem->setToolTip(region_name.c_str());
            rectItem->setZValue(1);

            // Determine color based on name
            QColor rectColor;
            if(region_name.starts_with("MPI_")) {
                rectColor = Qt::green;
            } else if(region_name.starts_with("!$omp")) {
                rectColor = Qt::red;
            } else {
                rectColor = Qt::lightGray;
            }
            rectItem->setBrush(rectColor);
        }

        top += ROW_HEIGHT;
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

    auto sceneHeight = TOP_MARGIN + X_AXIS_HEIGHT
            + data->getSelection()->getSlots().size() * ROW_HEIGHT
            + BOTTOM_MARGIN;
    auto sceneRect = rect();
    sceneRect.setHeight(sceneHeight);

    scene->setSceneRect(sceneRect);
    populateScene(scene);
    setScene(scene);
}