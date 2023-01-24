#ifndef MOTIV_TRACEDATAPROXY_HPP
#define MOTIV_TRACEDATAPROXY_HPP


#include <QObject>

#include "src/models/filetrace.hpp"
#include "src/models/ViewSettings.hpp"


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
    TraceDataProxy(FileTrace *trace, ViewSettings *settings, QObject *parent = nullptr);
    ~TraceDataProxy() override;


public: // methods
    [[nodiscard]] Trace *getSelection() const;
    [[nodiscard]] types::TraceTime getBegin() const;
    [[nodiscard]] types::TraceTime getEnd() const;
    [[nodiscard]] ViewSettings *getSettings() const;
    [[nodiscard]] Slot *getSelectedSlot() const;

    /**
     * Returns the runtime of the entire loaded trace
     * @return
     */
    [[nodiscard]] types::TraceTime getTotalRuntime() const;

public: Q_SIGNALS:
    /**
     * Signals the selection has been changed
     */
    void selectionChanged();
    /**
     * Signals the begin was changed
     */
    void beginChanged(types::TraceTime newBegin);
    /**
     * Signals the end was changed
     */
    void endChanged(types::TraceTime newEnd);
    /**
     * Signals a change to the selected slot, nullptr if none
     */
     void slotSelectionChanged();

    /**
     * Signals the filter was changes
     */
    void filterChanged(Filter);

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
    /**
     * Change the start and end time of the selection
     * @param newBegin
     * @param newEnd
     * @invariant @c newBegin may not be larger than end or total runtime
     * @invariant @c newEnd may not be smaller than begin and not larger than runtime
     */
    void setSelection(types::TraceTime newBegin, types::TraceTime newEnd);

    /**
     * Change the filter
     * @param filter
     */
    void setFilter(Filter filter);

    /**
     * Change the selected slot
     * @param newSlot pass nullptr if none selected
     */
    void setSlotSelection(Slot *newSlot);

private: // methods
    void updateSelection();
    void updateSlotSelection();

private: // data
    FileTrace *trace = nullptr;
    Trace *selection = nullptr;
    ViewSettings *settings = nullptr;

    types::TraceTime begin{0};
    types::TraceTime end{0};

    Slot *selectedSlot = nullptr;
};


#endif //MOTIV_TRACEDATAPROXY_HPP
