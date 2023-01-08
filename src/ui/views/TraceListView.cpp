#include "TraceListView.hpp"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

/*
 * TODO
 * - filtering (e.g. don't display barriers)
 */

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

int calculateScenePosition(unsigned long selectionBegin, unsigned long selectionRuntime,
                           unsigned long timepoint, int sceneWidth) {
    return (LEADING_MARGIN + Y_AXIS_WIDTH)
    + (static_cast<qreal>(timepoint - selectionBegin) / static_cast<qreal>(selectionRuntime)) * sceneWidth;
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
            // addSlot
        }

        top += ROW_HEIGHT;
    }

    // Create P2P communications
    for (const auto& comm : selection->getCommunications()) {
        auto source = comm.getStart();
        auto destination = comm.getEnd();

        qDebug() << "[Communication]"
            << "Source:" << source->getLocation().location_group().name().str().c_str()
            << "Destination:" << destination->getLocation().location_group().name().str().c_str();
    }

    // Create collective communications
    for (const auto& comm : selection->getCollectiveCommunications()) {
        qDebug() << "[CollectiveCommunicationsEvent]"
                 << "Start:" << comm.getStart().count()
                 << "End:" << comm.getEnd().count()
                 << "Root:" << comm.getRoot()
                 << "Location:" << comm.getLocation().name().str().c_str()
                 << "Location Group:" << comm.getLocation().location_group().name().str().c_str()
                 << "Events:" << comm.getLocation().num_events();
        auto op = comm.getOperation();
        switch (op) {
            case otf2::common::collective_type::barrier: {
                qDebug() << "Barrier";
                auto begin = calculateScenePosition(selectionBegin, selectionRuntime, comm.getStart().count(), sceneWidth);
                auto end = calculateScenePosition(selectionBegin, selectionRuntime, comm.getEnd().count(), sceneWidth);

                QRect barrierRect(begin, (TOP_MARGIN + X_AXIS_HEIGHT), end - begin, height());
                auto rectItem = scene->addRect(barrierRect);
                rectItem->setBrush(Qt::darkCyan);
                rectItem->setZValue(2);
                break;
            }
            case otf2::common::collective_type::broadcast:
                break;
            case otf2::common::collective_type::gather:
                break;
            case otf2::common::collective_type::gatherv:
                break;
            case otf2::common::collective_type::scatter:
                break;
            case otf2::common::collective_type::scatterv:
                break;
            case otf2::common::collective_type::all_gather:
                break;
            case otf2::common::collective_type::all_gatherv:
                break;
            case otf2::common::collective_type::all_to_all:
                break;
            case otf2::common::collective_type::all_to_allv:
                break;
            case otf2::common::collective_type::all_to_allw:
                break;
            case otf2::common::collective_type::all_reduce:
                break;
            case otf2::common::collective_type::reduce:
                break;
            case otf2::common::collective_type::reduce_scatter:
                break;
            case otf2::common::collective_type::scan:
                break;
            case otf2::common::collective_type::exscan:
                break;
            case otf2::common::collective_type::reduce_scatter_block:
                break;
            case otf2::common::collective_type::create_handle:
                break;
            case otf2::common::collective_type::destroy_handle:
                break;
            case otf2::common::collective_type::allocate:
                break;
            case otf2::common::collective_type::deallocate:
                break;
            case otf2::common::collective_type::create_handle_and_allocate:
                break;
            case otf2::common::collective_type::destroy_handle_and_deallocate:
                break;
        }
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