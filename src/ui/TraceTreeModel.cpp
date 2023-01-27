#include "TraceTreeModel.hpp"

TraceTreeModel::TraceTreeModel(TraceTree *tree, QObject *parent) : QAbstractItemModel(parent), tree_(tree) {}
