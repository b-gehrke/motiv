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

private: //methods
    void createMenus();
    void createToolBar();
    void createDockWidgets();
    void createCentralWidget();

private: // ui elements
    QToolBar *toolbar;
    QList<QDockWidget *> dockWidgets;

    view::Preview *traceOverview;
    view::TraceList *traceList;
    view::SelectionDetails *details;

private: // data
    std::shared_ptr<Trace> trace;
};


#endif // MOTIV_MAINWINDOW_HPP
