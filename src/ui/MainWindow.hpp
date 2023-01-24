#ifndef MOTIV_MAINWINDOW_HPP
#define MOTIV_MAINWINDOW_HPP


#include <QMainWindow>

#include "TimeInputField.hpp"
#include "TraceDataProxy.hpp"
#include "src/readercallbacks.hpp"
#include "SlotInformationDock.hpp"

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
    // TODO

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
};


#endif //MOTIV_MAINWINDOW_HPP
