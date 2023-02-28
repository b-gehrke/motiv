/*
 * Marvelous OTF2 Traces Interactive Visualizer (MOTIV)
 * Copyright (C) 2023 Florian Gallrein, Björn Gehrke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "TraceDataProxy.hpp"
#include "src/models/UITrace.hpp"

TraceDataProxy::TraceDataProxy(FileTrace *trace, ViewSettings *settings, QObject *parent)
    : QObject(parent), trace(trace), settings(settings), begin(trace->getStartTime()),
      end(trace->getStartTime() + trace->getRuntime()) {
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
    delete selection;
    auto subtrace = trace->subtrace(begin, end);
    selection = UITrace::forResolution(subtrace, subtrace->getRuntime() / 1920);
    Q_EMIT selectionChanged(begin, end);
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

    if(oldBegin != begin || oldEnd != end) {
        updateSelection();
    }
}

void TraceDataProxy::setTimeElementSelection(TimedElement *newSlot) {
    Q_EMIT infoElementSelected(newSlot);
}

void TraceDataProxy::setFilter(Filter filter) {
    settings->setFilter(filter);

    Q_EMIT filterChanged(filter);
}

Trace *TraceDataProxy::getFullTrace() const {
    return trace;
}
