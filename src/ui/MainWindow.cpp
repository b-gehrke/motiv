#include "MainWindow.hpp"

#include <QHBoxLayout>
#include <QMenuBar>
#include <QToolBar>

#include "TimeInputField.hpp"


MainWindow::MainWindow() : QMainWindow(nullptr) {
    this->createMenus();
    this->createToolBars();
    this->createDockWidgets();
    this->createCentralWidget();
}

void MainWindow::createMenus() {
    auto menuBar = this->menuBar();

    /// File menu
    auto openTraceAction = new QAction(tr("&Open..."), this);
    openTraceAction->setShortcut(tr("Ctrl+O"));
    connect(openTraceAction, SIGNAL(triggered()), this, SLOT(openTrace()));

    auto quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    auto fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(openTraceAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    /// View Menu
    auto filterAction = new QAction(tr("&Filter"));
    // TODO S for sieve? what might be more intuitive?
    filterAction->setShortcut(tr("Ctrl+S"));
    // TODO add actual slot
//    connect(filterAction, SIGNAL(triggered()), this, SLOT(openFilterPopup()));

    auto searchAction = new QAction(tr("&Find"));
    searchAction->setShortcut(tr("Ctrl+F"));
    // TODO add actual slot
//    connect(searchAction, SIGNAL(triggered()), this, SLOT(openFilterPopup()));

    auto viewMenu = menuBar->addMenu(tr("&View"));
    viewMenu->addAction(filterAction);
    viewMenu->addAction(searchAction);

    /// Window menu
    auto minimizeAction = new QAction(tr("&Minimize"), this);
    minimizeAction->setShortcut(tr("Ctrl+M"));
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(showMinimized()));

    auto windowMenu = menuBar->addMenu(tr("&Window"));
    windowMenu->addAction(minimizeAction);

    /// Help menu
    auto aboutAction = new QAction(tr("&View license"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(openLicenseView()));

    auto helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars() {
    // Top toolbar contains preview/control of whole trace
    this->topToolbar = new QToolBar(this);
    this->topToolbar->setMovable(false);
    addToolBar(Qt::TopToolBarArea, this->topToolbar);

    // Bottom toolbar contains control fields
    this->bottomToolbar = new QToolBar(this);
    this->bottomToolbar->setMovable(false);
    addToolBar(Qt::BottomToolBarArea, this->bottomToolbar);

    auto bottomContainerWidget = new QWidget(this->bottomToolbar);
    auto containerLayout = new QHBoxLayout(bottomContainerWidget);
    bottomContainerWidget->setLayout(containerLayout);

    this->startTimeInputField = new TimeInputField("Start", TimeUnit::Second, types::TraceTime(0), bottomContainerWidget);
    containerLayout->addWidget(this->startTimeInputField);
    this->endTimeInputField = new TimeInputField("Start", TimeUnit::Second, types::TraceTime(0), bottomContainerWidget);
    containerLayout->addWidget(this->endTimeInputField);

    this->bottomToolbar->addWidget(bottomContainerWidget);

}

void MainWindow::createDockWidgets() {

}

void MainWindow::createCentralWidget() {

}
