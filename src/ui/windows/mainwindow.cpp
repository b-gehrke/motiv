#include "mainwindow.hpp"
#include "src/readercallbacks.hpp"
#include "src/ui/views/TraceInformationDock.hpp"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QStringListModel>
#include <QWidget>
#include <QLineEdit>

MainWindow::MainWindow(QString path, QWidget *parent) : filePath(std::move(path)) {
    if (filePath.isEmpty()) {
        getTraceFilePath();
    }
    loadTraceFile(filePath);

    createMenus();
    // contains buttons and overview
    createToolBars();
    // contains details
    createDockWidgets();
    // contains list of processes
    createCentralWidget();
}

void MainWindow::createMenus() {
    /// File menu
    // "Open Trace" menu entry
    auto openTraceAction = new QAction(tr("&Open Trace"), this);
    openTraceAction->setShortcut(tr("Ctrl+O"));
    connect(openTraceAction, SIGNAL(triggered()), this, SLOT(openTrace()));

    // "Close Trace" menu entry
    auto closeTraceAction = new QAction(tr("&Close Trace"), this);
    closeTraceAction->setShortcut(tr("Ctrl+W"));
    connect(closeTraceAction, SIGNAL(triggered()), this, SLOT(closeTrace()));

    // "Quit" menu entry
    auto quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    auto fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openTraceAction);
    fileMenu->addSeparator();
    fileMenu->addAction(closeTraceAction);
    fileMenu->addAction(quitAction);

    /// View Menu
    // "Filter" menu entry
    auto filterAction = new QAction(tr("&Filter"));
    // TODO S for sieve? what might be more intuitive?
    filterAction->setShortcut(tr("Ctrl+S"));
    // TODO add actual slot
    connect(filterAction, SIGNAL(triggered()), this, SLOT(openFilterPopup()));

    // "Search" menu entry
    auto searchAction = new QAction(tr("&Search"));
    searchAction->setShortcut(tr("Ctrl+F"));
    // TODO add actual slot
    connect(searchAction, SIGNAL(triggered()), this, SLOT(openFilterPopup()));

    auto viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(filterAction);
    viewMenu->addAction(searchAction);

    /// Help menu
    // "View license" menu entry
    auto aboutAction = new QAction(tr("&View license"), this);
    // TODO connect to actual action
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(close()));

    auto helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars() {
    // Top toolbar contains preview/control of whole trace
    topToolbar = new QToolBar(this);
    topToolbar->setMovable(false);
    addToolBar(Qt::TopToolBarArea, topToolbar);

    preview = new view::Preview(trace, this);
    topToolbar->addWidget(preview);

    // Bottom toolbar contains control fields
    bottomToolbar = new QToolBar(this);
    bottomToolbar->setMovable(false);
    addToolBar(Qt::BottomToolBarArea, bottomToolbar);

    auto containerWidget = new QWidget(bottomToolbar);
    auto containerLayout = new QHBoxLayout(containerWidget);
    containerWidget->setLayout(containerLayout);
    containerLayout->addWidget(new QLabel("Start:", containerWidget));
    containerLayout->addWidget(new QLineEdit("0", containerWidget));
    containerLayout->addWidget(new QLabel("End:", containerWidget));
    containerLayout->addWidget(new QLineEdit("0", containerWidget));
    bottomToolbar->addWidget(containerWidget);
}

void MainWindow::createDockWidgets() {
    auto traceInformation = new view::TraceInformationDock(trace, this);
    addDockWidget(Qt::RightDockWidgetArea, traceInformation);
}

void MainWindow::createCentralWidget() {
    traceList = new view::TraceList(selection, this);
    setCentralWidget(traceList);
}

void MainWindow::updateView(otf2::chrono::duration start, otf2::chrono::duration end) {
//    viewStart = start;
//    viewEnd = end;
}

void MainWindow::loadTraceFile(const QString &path) {
    otf2::reader::reader reader(filePath.toStdString());
    ReaderCallbacks cb(reader);

    reader.set_callback(cb);
    reader.read_definitions();
    reader.read_events();

    trace = std::make_shared<FileTrace>(*cb.getSlots(), *cb.getCommunications(), cb.duration());
    selection = std::make_shared<SubTrace>(trace->getSlots(), trace->getCommunications(), trace->getRuntime());

    viewStart = 0;
    viewEnd = selection->getRuntime().count();
}

QString MainWindow::getTraceFilePath() {
    filePath = QFileDialog::getOpenFileName(this, QFileDialog::tr("Open trace"), QString(),
                                            QFileDialog::tr("OTF Traces (*.otf *.otf2)"));

    if (filePath.isEmpty()) {
        // TODO
    }

    return filePath;
}