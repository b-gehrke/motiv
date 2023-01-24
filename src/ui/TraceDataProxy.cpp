#include "TraceDataProxy.hpp"
#include "src/models/uitrace.hpp"

TraceDataProxy::TraceDataProxy(FileTrace *trace, ViewSettings *settings, QObject *parent)
    : QObject(parent), trace(trace), begin(trace->getStartTime()), end(trace->getStartTime() + trace->getRuntime()),
      settings(settings) {
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
    setSelection(newBegin, end);
}

void TraceDataProxy::setSelectionEnd(types::TraceTime newEnd) {
    setSelection(begin, newEnd);
}

ViewSettings *TraceDataProxy::getSettings() const {
    return settings;
}


types::TraceTime TraceDataProxy::getTotalRuntime() const {
    return trace->getRuntime();
}

void TraceDataProxy::updateSelection() {
    auto subtrace = trace->subtrace(begin, end);
    selection = UITrace::forResolution(subtrace, subtrace->getRuntime() / 1920);
//    selection = subtrace;
    Q_EMIT selectionChanged();
}

void TraceDataProxy::setSelection(types::TraceTime newBegin, types::TraceTime newEnd) {
    newBegin = qMax(types::TraceTime(0), newBegin);
    newEnd = qMin(getTotalRuntime(), newEnd);

    newBegin = qMin(newEnd, newBegin);
    newEnd = qMax(newBegin, newEnd);

    auto oldBegin = begin;
    auto oldEnd = end;

    begin = newBegin;
    end=newEnd;

    if(oldBegin != begin) {
        Q_EMIT beginChanged(begin);
    }

    if(oldEnd != end) {
        Q_EMIT endChanged(end);
    }

    updateSelection();
}
