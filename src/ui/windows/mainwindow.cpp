#include "mainwindow.hpp"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QStringListModel>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), dockWidgets() {
  createMenus();
  // contains buttons and overview
  createToolBar();
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

  /// Help menu
  // "View license" menu entry
  auto aboutAction = new QAction(tr("&View license"), this);
  // TODO connect to actual action
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(close()));

  auto helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBar() {
    toolbar = addToolBar(tr("&Toolbar"));
    toolbar->setMovable(false);

    preview = new view::Preview(trace, this);
    toolbar->addWidget(preview);
}

void MainWindow::createDockWidgets() {
    auto traceInformation = new view::TraceInformationDock(trace, this);
    addDockWidget(Qt::RightDockWidgetArea, traceInformation);
}

void MainWindow::createCentralWidget() {
    traceList = new view::TraceList(trace, this);
    setCentralWidget(traceList);
}