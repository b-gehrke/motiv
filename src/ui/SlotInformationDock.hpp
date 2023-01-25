#ifndef MOTIV_SLOTINFORMATIONDOCK_HPP
#define MOTIV_SLOTINFORMATIONDOCK_HPP


#include <QDockWidget>
#include <QFormLayout>
#include <QLabel>

#include "TraceDataProxy.hpp"
#include "TimeUnitLabel.hpp"

class SlotInformationDock : public QDockWidget {
    Q_OBJECT

public:
    explicit SlotInformationDock(QWidget *parent = nullptr);

public: Q_SIGNALS:
    void zoomToWindow(types::TraceTime from, types::TraceTime to);

public Q_SLOTS:
    void setSlot(Slot *slot);
    void zoomIntoViewPressed();

protected:
    void updateView();

private: // fields
    Slot *slot_ = nullptr;

private: // widgets
    QWidget *child = nullptr;
    QFormLayout *childLayout = nullptr;
    QLabel *nameField = nullptr;
    QLabel *rankField = nullptr;
    TimeUnitLabel *startField = nullptr;
    TimeUnitLabel *endField = nullptr;
    TimeUnitLabel *runtimeField = nullptr;
};


#endif //MOTIV_SLOTINFORMATIONDOCK_HPP
