#ifndef MOTIV_SLOTINFORMATIONDOCK_HPP
#define MOTIV_SLOTINFORMATIONDOCK_HPP


#include <QDockWidget>

#include "TraceDataProxy.hpp"

class SlotInformationDock : public QDockWidget {
    Q_OBJECT

public:
    explicit SlotInformationDock(TraceDataProxy *data, QWidget *parent = nullptr);

protected Q_SLOTS:
    void updateInformation();

private:
    void addInformation();
    void clearInformation();

private:
    TraceDataProxy *data = nullptr;

};


#endif //MOTIV_SLOTINFORMATIONDOCK_HPP
