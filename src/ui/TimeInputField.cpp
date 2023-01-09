#include "TimeInputField.hpp"

#include <QHBoxLayout>
#include <QValidator>
#include <utility>


TimeUnit::TimeUnit(TimeUnit::Unit unit) : unit(unit) {}

QString TimeUnit::str() const {
    switch (this->unit) {
        case NanoSecond:
            return "ns";
        case MicroSecond:
            return "μs";
        case MilliSecond:
            return "ms";
        case Second:
            return "s";
        case Minute:
            return "m";
        case Hour:
            return "h";
        default:
            throw std::invalid_argument("Unknown TimeUnit");
    }
}

TimeUnit::TimeUnit(QString unit) {
    std::map<QString, Unit> lut = {
            {"ns", NanoSecond},
            {"μs", MicroSecond},
            {"ms", MilliSecond},
            {"s", Second},
            {"m", Minute},
            {"h", Hour},
    };

    auto it = lut.find(unit);
    if (it == lut.end()) {
        throw std::invalid_argument("Unknown TimeUnit");
    }

    this->unit = it->second;
}

double TimeUnit::multiplier() {
    switch (this->unit) {
        case TimeUnit::NanoSecond:
            return 1;
        case TimeUnit::MicroSecond:
            return 1e3;
        case TimeUnit::MilliSecond:
            return 1e6;
        case TimeUnit::Second:
            return 1e9;
        case TimeUnit::Minute:
            return 60e9;
        case TimeUnit::Hour:
            return 60 * 60e9;
        default:
            // This should be caught by the constructors
            __builtin_unreachable();
    }
}


TimeInputField::TimeInputField(QString text, TimeUnit resolution, types::TraceTime initialTime, QWidget *parent)
    : QWidget(parent), text(std::move(text)), resolution(resolution), time(initialTime) {

    this->textLabel = new QLabel(this->text, this);

    this->lineEdit = new QLineEdit(QString::number(this->time.count()), this);
    this->lineEdit->setValidator(new QDoubleValidator(this));

    this->comboBox = new QComboBox(this);
    for (const auto &unit : TIME_UNITS) {
        this->comboBox->addItem(unit.str());
    }
    this->comboBox->setCurrentText(resolution.str());

    auto layout = new QHBoxLayout(this);
    layout->addWidget(this->textLabel);
    layout->addWidget(this->lineEdit);
    layout->addWidget(this->comboBox);
    this->setLayout(layout);

    connect(this->comboBox, &QComboBox::currentTextChanged, [this] (const auto &newValue) {
        this->resolution = TimeUnit(newValue);
        double newTextValue = static_cast<double>(time.count()) / this->resolution.multiplier();
        this->lineEdit->setText(QString::number(newTextValue));
    });

    connect(this->lineEdit, &QLineEdit::returnPressed, [this] {
        double newValue = this->lineEdit->text().toDouble();
        auto newTotalValue = static_cast<u_int64_t>(newValue * this->resolution.multiplier());
        this->time = types::TraceTime(newTotalValue);
    });
}
