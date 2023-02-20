#include "TimeInputField.hpp"

#include <QHBoxLayout>
#include <QValidator>
#include <utility>


TimeInputField::TimeInputField(QString text, TimeUnit resolution, types::TraceTime initialTime, QWidget *parent)
    : QWidget(parent), text(std::move(text)), resolution(resolution), time(0) {

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
        this->setTime(types::TraceTime(newTotalValue));
    });

    setTime(initialTime);
}

void TimeInputField::setUpdateFunction(std::function<void(types::TraceTime)> newUpdateFunction) {
    this->updateFunction = std::move(newUpdateFunction);
}

void TimeInputField::setTime(types::TraceTime newTime) {
    if(newTime != time) {
        this->time = newTime;
        if (this->updateFunction) {
            this->updateFunction(this->time);
        }

        double newTextValue = static_cast<double>(time.count()) / this->resolution.multiplier();
        this->lineEdit->setText(QString::number(newTextValue));
    }
}
