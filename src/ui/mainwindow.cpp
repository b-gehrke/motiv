#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QStringListModel>
#include <QVBoxLayout>
#include <otf2xx/otf2.hpp>

#include "src/models/slot.hpp"
#include "src/models/communication.hpp"
#include "src/readercallbacks.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this->ui->actionOpen_Trace, &QAction::triggered, this, &MainWindow::openTrace);
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::openTrace() {
    QString fileName = QFileDialog::getOpenFileName(this);

    this->loadTrace(fileName.toStdString());
}

void MainWindow::loadTrace(const std::string& path) {
    otf2::reader::reader reader(path);

    ReaderCallbacks cb(reader);

    reader.set_callback(cb);
    reader.read_definitions();
    reader.read_events();

    this->trace = std::make_shared<Trace>(cb.getSlots(), cb.getCommunications(), cb.duration());
    this->showTrace(this->trace->slotss->begin()->start, this->trace->slotss->begin()->start + this->trace->runtime);
}

void MainWindow::showTrace(otf2::chrono::duration, otf2::chrono::duration) {
    int maxWidth = this->ui->frame->width() - 8;
    long double runtime = this->trace->runtime.count();

    auto model = new QStringListModel();
    QStringList items;

    for (auto &&slot: *this->trace->slotss) {
        std::string region = slot.region.name().str();
        std::string rank(slot.location.location_group().name());
        std::string thread(slot.location.name());
        auto start = slot.start;
        auto end = slot.end;

        long double duration = (end - start).count();
        int width = static_cast<int>((duration / runtime) * maxWidth);


        unsigned int r = slot.location.location_group().ref().get();
        int y = static_cast<int>(r * 30 + 4);
        int x = static_cast<int>((start.count() / runtime) * maxWidth + 4);

        QString text = QString::fromStdString(region);
        auto *label = new QLabel(this->ui->frame);

        label->setText(text);
        label->setStyleSheet("QLabel { background-color: fuchsia; border-left: 1px solid black; }");
        label->setToolTip(text);
        label->resize(width, 16);
        label->move(x, y);
        label->show();

        QString item = QString::fromStdString(rank) + " " + text;
        items << item;
    }

    model->setStringList(items);
    this->ui->listView->setModel(model);
}
