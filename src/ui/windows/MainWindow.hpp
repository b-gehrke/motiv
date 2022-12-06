#ifndef MOTIV_MAINWINDOW_HPP
#define MOTIV_MAINWINDOW_HPP

#include <QMainWindow>
#include <QToolBar>

#include "src/models/trace.hpp"
#include "src/ui/views/SelectionDetails.hpp"
#include "src/ui/views/TraceList.hpp"
#include "src/ui/views/Preview.hpp"
#include "src/readercallbacks.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public: //constructors
    explicit MainWindow(QString filePath = QString(), QWidget *parent = nullptr);

public Q_SLOTS: // slots
    QString getTraceFilePath();
    void loadTraceFile(const QString &path);
    void updateView(otf2::chrono::duration start, otf2::chrono::duration end);

    void openLicenseView();

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
    std::shared_ptr<otf2::reader::reader> reader;
    std::shared_ptr<ReaderCallbacks> reader_callbacks;
    QString filePath;
    std::shared_ptr<Trace> trace = nullptr;
    std::shared_ptr<SubTrace> selection = nullptr;
    // start and endpoint of the current view on the trace
    long long int viewStart;
    long long int viewEnd;
};


#endif // MOTIV_MAINWINDOW_HPP
