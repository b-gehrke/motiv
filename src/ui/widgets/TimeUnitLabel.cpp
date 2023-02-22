#include "TimeUnitLabel.hpp"

#include "src/ui/TimeUnit.hpp"

TimeUnitLabel::TimeUnitLabel(double time, QWidget *parent) : QLabel(parent), time(time) {
    updateView();
}

void TimeUnitLabel::setTime(double t) {
    if(t == time) return;
    time = t;

    updateView();
}

double TimeUnitLabel::getTime() const {
    return time;
}

void TimeUnitLabel::updateView() {
    QString unitStr;
    QString timeStr = "0";

    for(const auto &unit : TIME_UNITS) {
        auto m = unit.multiplier();
        if (this->time >= m) {
            unitStr = unit.str();
            timeStr = QString::number(this->time/m, 'f');
        } else {
            break;
        }
    }
    this->setText(timeStr + unitStr);
}

