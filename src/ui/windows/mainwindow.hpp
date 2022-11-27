#ifndef MOTIV_MAINWINDOW_HPP
#define MOTIV_MAINWINDOW_HPP

#include <QMainWindow>
#include <QToolBar>

#include "src/models/trace.hpp"
#include "src/ui/views/selectiondetails.hpp"
#include "src/ui/views/tracelist.hpp"
#include "src/ui/views/preview.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public Q_SLOTS: // slots
    void updateView(otf2::chrono::duration start, otf2::chrono::duration end);

private: //methods
    void createMenus();
    void createToolBars();
    void createDockWidgets();
    void createCentralWidget();

private: // ui elements
    QToolBar *topToolbar = nullptr;
    QToolBar *bottomToolbar = nullptr;
    QList<QDockWidget *> dockWidgets;

    view::Preview *preview = nullptr;
    view::TraceList *traceList = nullptr;
    view::SelectionDetails *details = nullptr;

private: // data
    std::shared_ptr<Trace> trace = nullptr;
    // start and endpoint of the current view on the trace
    otf2::chrono::duration viewStart;
    otf2::chrono::duration viewEnd;
};


#endif // MOTIV_MAINWINDOW_HPP
