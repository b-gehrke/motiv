#include "TraceDataProxy.hpp"

TraceDataProxy::TraceDataProxy(FileTrace *trace, QObject *parent) : QObject(parent), trace(trace), begin(trace->getStartTime()), end(trace->getStartTime() + trace->getRuntime()) {
    updateSelection();
}

TraceDataProxy::~TraceDataProxy() {
    delete this->selection;
    delete this->trace;
}

Trace *TraceDataProxy::getSelection() const {
    return this->selection;
}

types::TraceTime TraceDataProxy::getBegin() const {
    return this->begin;
}

types::TraceTime TraceDataProxy::getEnd() const {
    return this->end;
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
    selection = trace->subtrace(begin, end);
    Q_EMIT selectionChanged();
}