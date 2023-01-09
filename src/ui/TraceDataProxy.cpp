#include "TraceDataProxy.hpp"

TraceDataProxy::TraceDataProxy(FileTrace *trace, QObject *parent) : QObject(parent), trace(trace), begin(trace->getStartTime()), end(trace->getStartTime() + trace->getRuntime()) {
    updateSelection();
}

TraceDataProxy::~TraceDataProxy() {
    delete this->trace;
}

void TraceDataProxy::setSelectionBegin(types::TraceTime newBegin) {
    assert(newBegin < trace->getRuntime());
    assert(newBegin <= end);
    begin = newBegin;

    Q_EMIT beginChanged();

    updateSelection();
}

void TraceDataProxy::setSelectionEnd(types::TraceTime newEnd) {
    assert(newEnd < trace->getRuntime());
    assert(newEnd >= begin);
    end = newEnd;

    Q_EMIT endChanged();

    updateSelection();
}

void TraceDataProxy::updateSelection() {
    selection = dynamic_cast<SubTrace *>(trace->subtrace(begin, end).get());
    Q_EMIT selectionChanged();
}