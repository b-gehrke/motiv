#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

#include <otf2xx/otf2.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this->ui->pushButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

class ReaderCallbacks : public otf2::reader::callback
{
    using otf2::reader::callback::event;
    using otf2::reader::callback::definition;
private:
    
public:
    ReaderCallbacks(){};
    ~ReaderCallbacks(){};
};



void MainWindow::onButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this);

    otf2::reader::reader reader(fileName.toStdString());

    ReaderCallbacks cb;

    reader.set_callback(cb);
    reader.read_definitions( );

    auto registry = reader.registry();
    auto locations = registry.all<otf2::definition::location>();

    for (auto &&location : locations)
    {
        QString buff;
        QString line = buff.asprintf("Location %d: %s", location.ref(), location.name().str().c_str()); 
        this->ui->textBrowser->append(line);
    }
    

}

