#include "mainwindow.hpp"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QWidget>

#include "src/models/communication.hpp"
#include "src/models/filetrace.hpp"
#include "src/models/slot.hpp"
#include "src/readercallbacks.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  createMenus();
  createCentralWidget();
}

MainWindow::~MainWindow() {}

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

void MainWindow::createCentralWidget() {
  auto vertSplit = new QWidget(this);
  vertSplit->setLayout(new QVBoxLayout(vertSplit));
  // vertSplit->layout()->setSizeConstraint(QLayout::SetMaximumSize);
  auto horiSplit = new QWidget(vertSplit);
  horiSplit->setLayout(new QHBoxLayout(horiSplit));
  // horiSplit->layout()->setSizeConstraint(QLayout::SetMaximumSize);

  overview = new view::TraceOverview(this);
  vertSplit->layout()->addWidget(overview);
  vertSplit->layout()->addWidget(horiSplit);

  details = new view::SelectionDetails(this);
  tracelist = new view::TraceList(this);

  horiSplit->layout()->addWidget(tracelist);
  horiSplit->layout()->addWidget(details);

  setCentralWidget(vertSplit);
}