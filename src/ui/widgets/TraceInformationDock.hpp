#ifndef MOTIV_TRACEINFORMATIONDOCK_HPP
#define MOTIV_TRACEINFORMATIONDOCK_HPP

#include <QWidget>
#include <QDockWidget>
#include "src/models/trace.hpp"


    class TraceInformationDock : public QDockWidget {
    public: // constructors
        TraceInformationDock(std::shared_ptr<Trace> tracePtr, QWidget *parent);

    private: //data
        std::shared_ptr<Trace> trace;
    };



#endif //MOTIV_TRACEINFORMATIONDOCK_HPP
