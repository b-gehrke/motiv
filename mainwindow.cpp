#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <QStringListModel>

#include <otf2xx/otf2.hpp>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this->ui->actionOpen_Trace, &QAction::triggered, this, &MainWindow::openTrace);
}

MainWindow::~MainWindow()
{
    delete ui;
}

struct Slot {
    otf2::chrono::duration start;
    otf2::chrono::duration end;
    otf2::definition::location location;
    otf2::definition::region region;
};

struct Communication {
    otf2::chrono::duration start;
    otf2::chrono::duration end;
    std::string from;
    std::string to;

};

class ReaderCallbacks : public otf2::reader::callback
{
//    using otf2::reader::callback::event;
//    using otf2::reader::callback::definition;
private:
    std::vector<Slot> slots_;
    std::vector<Communication> communications_;

    std::map<otf2::reference<otf2::definition::location>, std::vector<Slot>*> slots_building_;
//    std::vector<Slot> slots_building_;

    otf2::chrono::time_point program_start_;
    otf2::chrono::time_point program_end_;

    otf2::reader::reader& rdr_;
public:
    ReaderCallbacks(otf2::reader::reader& rdr) : rdr_(rdr), slots_(), communications_(), slots_building_(), program_start_() {

    }

    void definition(const otf2::definition::location& loc) override
    {
        rdr_.register_location(loc);
    }

    void event(const otf2::definition::location &location, const otf2::event::program_begin &event) override {
        this->program_start_ = event.timestamp();
    }

    void event(const otf2::definition::location &location, const otf2::event::program_end &event) override {
        this->program_end_ = event.timestamp();
    }

    void event(const otf2::definition::location &location, const otf2::event::enter &event) override {
        auto start = event.timestamp() - this->program_start_;

        Slot slot {
            .start = start,
            .location = location,
            .region = event.region(),
        };

        std::vector<Slot>* locationStack;
        auto locationStackIt = this->slots_building_.find(location.ref());
        if(locationStackIt == this->slots_building_.end()){
            locationStack = new std::vector<Slot>();
            this->slots_building_.insert({location.ref(), locationStack});
        } else {
            locationStack = locationStackIt->second;
        }

        locationStack->push_back(slot);
    }

    void event(const otf2::definition::location &location, const otf2::event::leave &event) override {
        auto locationStack = this->slots_building_.at(location.ref());

        Slot &slot = locationStack->back();
        locationStack->pop_back();


        slot.end = event.timestamp() - this->program_start_;

        this->slots_.push_back(slot);
    }

    inline std::vector<Slot>& getSlots() {
        return this->slots_;
    }
    inline std::vector<Communication>& getCommunications() {
        return this->communications_;
    }

    [[nodiscard]] inline otf2::chrono::duration duration() const {
        return this->program_end_ - this->program_start_;
    }

    void events_done(const otf2::reader::reader &) override {
        std::sort(this->slots_.begin(), this->slots_.end(), [](Slot& rhs, Slot& lhs) {
            return rhs.start < lhs.start;
        });

        for (const auto &item: this->slots_building_) {
            delete item.second;
        }
        std::destroy(this->slots_building_.begin(), this->slots_building_.end());
    }
};

void MainWindow::openTrace() {
    QString fileName = QFileDialog::getOpenFileName(this);

    otf2::reader::reader reader(fileName.toStdString());

    ReaderCallbacks cb(reader);

    reader.set_callback(cb);
    reader.read_definitions();
    reader.read_events();

    double maxWidth = this->ui->frame->width() - 8;
    double runtime = cb.duration().count();

    auto model = new QStringListModel();
    QStringList items;

    for(auto &&slot : cb.getSlots()) {
        std::string region = slot.region.name().str();
        std::string rank(slot.location.location_group().name());
        std::string thread(slot.location.name());
        auto start = slot.start;
        auto end = slot.end;

        double duration = (end - start).count();
        double width = (duration / runtime) * maxWidth;


        unsigned int r = slot.location.location_group().ref().get();
        long y = r * 30 + 4;
        long x = (start.count() / runtime) * maxWidth + 4;

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

