#ifndef MOTIV_MAINWINDOW_HPP
#define MOTIV_MAINWINDOW_HPP

#include <QMainWindow>

#include "src/models/trace.hpp"
#include "src/ui/views/selectiondetails.hpp"
#include "src/ui/views/tracelist.hpp"
#include "src/ui/views/traceoverview.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private: //methods
    void createMenus();
    void createCentralWidget();

private: // ui elements
    view::TraceOverview *overview;
    view::TraceList *tracelist;
    view::SelectionDetails *details;

private: // data
    std::shared_ptr<Trace> trace;
};


#endif // MOTIV_MAINWINDOW_HPP
