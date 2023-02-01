#ifndef MOTIV_MAINWINDOW_HPP
#define MOTIV_MAINWINDOW_HPP


#include <QMainWindow>

#include "src/ui/widgets/TimeInputField.hpp"
#include "src/ui/TraceDataProxy.hpp"
#include "src/ReaderCallbacks.hpp"
#include "src/ui/widgets/SlotInformationDock.hpp"
#include "src/ui/widgets/TraceOverviewDock.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public: // constructors
    MainWindow(QString filepath = QString());
    ~MainWindow() override;

public: // methods
    void setFilepath(QString newFilepath);

public: Q_SIGNALS:
    // TODO

public Q_SLOTS:
    void resetZoom();
    void openFilterPopup();
    void openNewTrace();

private: // methods
    void createMenus();
    void createToolBars();
    void createDockWidgets();
    void createCentralWidget();

    void promptFile();
    void loadTrace();
    void loadSettings();

private: // widgets
    QToolBar *topToolbar = nullptr;
    QToolBar *bottomToolbar = nullptr;

    SlotInformationDock *slotInformation = nullptr;

    TimeInputField *startTimeInputField = nullptr;
    TimeInputField *endTimeInputField = nullptr;

private: // properties
    QString filepath;
    TraceDataProxy *data = nullptr;

    otf2::reader::reader *reader = nullptr;
    ReaderCallbacks *callbacks = nullptr;

    ViewSettings *settings = nullptr;
    TraceOverviewDock *traceOverview = nullptr;
};


#endif //MOTIV_MAINWINDOW_HPP
