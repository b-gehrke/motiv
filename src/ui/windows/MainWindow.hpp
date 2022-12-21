#ifndef MOTIV_MAINWINDOW_HPP
#define MOTIV_MAINWINDOW_HPP

#include <QLineEdit>
#include <QMainWindow>
#include <QToolBar>

#include "src/models/trace.hpp"
#include "src/ui/TraceDataModel.hpp"
#include "src/ui/widgets/SelectionDetails.hpp"
#include "src/ui/views/TraceListView.hpp"
#include "src/ui/widgets/Preview.hpp"
#include "src/readercallbacks.hpp"
#include "src/ui/widgets/License.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public: //constructors
    explicit MainWindow(QString filePath = QString(), QWidget *parent = nullptr);

Q_SIGNALS:
    void selectionUpdated();

public Q_SLOTS: // slots
    void openTrace();

    void openLicenseView();

private: //methods
    void createMenus();
    void createToolBars();
    void createDockWidgets();
    void createCentralWidget();

    QString getTraceFilePath();
    void loadTraceFile(const QString &path);

private: // ui elements
    QToolBar *topToolbar = nullptr;
    QToolBar *bottomToolbar = nullptr;
    QList<QDockWidget *> dockWidgets;

    Preview *preview = nullptr;
    TraceListView *traceList = nullptr;
    SelectionDetails *details = nullptr;

    License *licenseWindow = nullptr;

    QLineEdit *intervalBegin = nullptr;
    QLineEdit *intervalEnd = nullptr;

private: // data
    std::shared_ptr<otf2::reader::reader> reader;
    std::shared_ptr<ReaderCallbacks> reader_callbacks;
    QString filePath;
    TraceDataModel *data;
};


#endif // MOTIV_MAINWINDOW_HPP
