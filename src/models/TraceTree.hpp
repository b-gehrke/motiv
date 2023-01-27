#ifndef MOTIV_TRACETREE_HPP
#define MOTIV_TRACETREE_HPP


#include "trace.hpp"

class TraceTree {
private:
public:
    TraceTree(Slot *data, std::vector<TraceTree *> children);

public:
    static std::map<otf2::definition::location_group*, TraceTree*> fromTrace(Trace* trace);
    static TraceTree* fromSlots(const Range<Slot*>& slots);

public:
    [[nodiscard]] Slot *getData() const;

    [[nodiscard]] const std::vector<TraceTree *> &getChildren() const;

private:
    Slot* data;
    std::vector<TraceTree*> children;
};


#endif //MOTIV_TRACETREE_HPP
