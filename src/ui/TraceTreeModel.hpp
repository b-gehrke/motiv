#ifndef MOTIV_TRACETREEMODEL_HPP
#define MOTIV_TRACETREEMODEL_HPP


#include <QAbstractItemModel>
#include "src/models/TraceTree.hpp"

class TraceTreeModel : public QAbstractItemModel {
public:
    TraceTreeModel(TraceTree *tree, QObject *parent = nullptr);

private:
    TraceTree* tree_;
};


#endif //MOTIV_TRACETREEMODEL_HPP
