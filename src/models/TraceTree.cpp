#include "TraceTree.hpp"

#include <utility>

TraceTree::TraceTree(Slot *data, std::vector<TraceTree *> children) : data(data), children(std::move(children)) {}

Slot *TraceTree::getData() const {
    return data;
}

const std::vector<TraceTree *> &TraceTree::getChildren() const {
    return children;
}

TraceTree *TraceTree::fromSlots(const Range<Slot *>& slots) {
    if(slots.empty()) {
        return new TraceTree(nullptr, std::vector<TraceTree*>());
    }

    std::vector<TraceTree *> children;

    auto nextFirst = slots.begin();
    auto first = nextFirst;

    while(nextFirst != slots.end()) {
        nextFirst = std::find_if(slots.begin(), slots.end(), [first](Slot* lhs){return lhs->start > (*first)->end;});

        auto subRange = Range<Slot*>(first + 1, nextFirst - 1);

        auto child = TraceTree::fromSlots(subRange);
        children.push_back(child);
    }

    return new TraceTree(*slots.begin(), children);
}

std::map<otf2::definition::location_group*, TraceTree*> TraceTree::fromTrace(Trace *trace) {
    std::map<otf2::definition::location_group*, TraceTree*> forest;

    for (const auto &item: trace->getSlots()) {
        forest.insert({item.first, fromSlots(item.second)});
    }

    return forest;
}
