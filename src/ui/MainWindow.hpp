#ifndef MOTIV_MAINWINDOW_HPP
#define MOTIV_MAINWINDOW_HPP


#include <QMainWindow>

#include "TimeInputField.hpp"
#include "TraceDataProxy.hpp"
#include "src/readercallbacks.hpp"

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

private: // widgets
    QToolBar *topToolbar = nullptr;
    QToolBar *bottomToolbar = nullptr;

    QList<QDockWidget *> *docks = nullptr;

    TimeInputField *startTimeInputField = nullptr;
    TimeInputField *endTimeInputField = nullptr;

private: // properties
    QString filepath;
    TraceDataProxy *data = nullptr;

    otf2::reader::reader *reader = nullptr;
    ReaderCallbacks *callbacks = nullptr;
};


#endif //MOTIV_MAINWINDOW_HPP
