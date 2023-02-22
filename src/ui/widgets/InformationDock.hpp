#ifndef MOTIV_INFORMATIONDOCK_HPP
#define MOTIV_INFORMATIONDOCK_HPP


#include "TimeUnitLabel.hpp"
#include "src/ui/TraceDataProxy.hpp"
#include "src/ui/widgets/infostrategies/InformationDockElementStrategy.hpp"
#include <QLabel>
#include <QFormLayout>
#include <QDockWidget>

class InformationDock : public QDockWidget {
Q_OBJECT
public:
    explicit InformationDock(QWidget *parent = nullptr);

public:
    void addElementStrategy(InformationDockElementStrategy *s);

public:
Q_SIGNALS:

    void zoomToWindow(types::TraceTime from, types::TraceTime to);

public Q_SLOTS:

    void zoomIntoViewPressed();

    void setElement(TimedElement *element);

protected:
    virtual void updateView();

private: // fields
    TimedElement *element_ = nullptr;

private:
    QWidget *child = nullptr;
    QFormLayout *childLayout = nullptr;

    std::vector<std::pair<QWidget*, InformationDockElementStrategy*>> strategies_ {};
};


#endif //MOTIV_INFORMATIONDOCK_HPP
