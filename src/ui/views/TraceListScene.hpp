#ifndef MOTIV_TRACELISTSCENE_HPP
#define MOTIV_TRACELISTSCENE_HPP

#include <QGraphicsScene>
#include "TraceListSlotItem.hpp"
#include "src/models/slot.hpp"

class TraceListScene : public QGraphicsScene {
    Q_OBJECT

public: // constructors
    // requirements:
    // runtime, start time (for header)
    // amount items? for height
    explicit TraceListScene(QObject *parent = nullptr) : QGraphicsScene(parent) {}

public: // methods
    TraceListSlotItem *addSlot(Slot *slot);
//    TraceListP2PCommunicationItem *addP2PCommunication(P2PCommunication *comm);
//    TraceListCollectiveCommunicationItem *addCollectiveCommunication(CollectiveCommunication * comm);

    int canvasHeight();
    int canvasWidth();

    void setRowHeight(int value);

private: // properties
    int xAxisHeight = 30;
    int yAxisWidth = 100;
    int leadingMargin = 5;
    int trailingMargin = 5;
    int topMargin = 5;
    int bottomMargin = 5;
    int rowHeight = 30;

    enum class Elevation : int {
        Background,
        Lines,
        Header,
        Slot,
        P2PCommunication,
        CollectiveCommunication,
    };

};


#endif //MOTIV_TRACELISTSCENE_HPP
