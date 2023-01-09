#ifndef MOTIV_TRACEDATAPROXY_HPP
#define MOTIV_TRACEDATAPROXY_HPP


#include <QObject>

#include "src/models/filetrace.hpp"


/**
 * TraceDataProxy acts as an intermediate class between the views and the data.
 * This class tracks all state changes related to the representation of the trace, e.g. selections.
 */
class TraceDataProxy : public QObject {
    Q_OBJECT

public: //constructors
    /**
     * Constructs a new TraceDataProxy.
     * The object takes ownership of the supplied FileTrace.
     * @param trace
     * @param parent
     */
    explicit TraceDataProxy(FileTrace *trace, QObject *parent = nullptr);
    ~TraceDataProxy();


public: // methods
    SubTrace *getSelection() const;
    types::TraceTime getBegin() const;
    types::TraceTime getEnd() const;

public: Q_SIGNALS:
    /**
     * Signals the selection has been changed
     */
    void selectionChanged();
    /**
     * Signals the begin was changed
     */
    void beginChanged();
    /**
     * Signal the end was changed
     */
    void endChanged();

public Q_SLOTS:
    /**
     * Change the start time of the selection
     * @param newBegin
     * @invariant may not be larger than end or total runtime
     */
    void setSelectionBegin(types::TraceTime newBegin);
    /**
     * Change the end time of the selection
     * @param newEnd
     * @invariant may not be smaller than begin and not larger than runtime
     */
    void setSelectionEnd(types::TraceTime newEnd);

private: // methods
    void updateSelection();

private: // data
    FileTrace *trace = nullptr;
    SubTrace *selection = nullptr;

    types::TraceTime begin{0};
    types::TraceTime end{0};
};


#endif //MOTIV_TRACEDATAPROXY_HPP
