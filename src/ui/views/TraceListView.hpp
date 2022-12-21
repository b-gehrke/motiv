//
// Created by Florian Gallrein on 19.12.22.
//

#ifndef MOTIV_TRACELISTVIEW_HPP
#define MOTIV_TRACELISTVIEW_HPP


#include <QGraphicsView>
#include "src/ui/TraceDataModel.hpp"

class TraceListView : public QGraphicsView {
    Q_OBJECT
public:
    TraceListView(TraceDataModel *data, QWidget *parent = nullptr);
};


#endif //MOTIV_TRACELISTVIEW_HPP
