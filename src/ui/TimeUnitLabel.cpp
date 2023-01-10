#include "TimeUnitLabel.hpp"

#include "TimeUnit.hpp"

TimeUnitLabel::TimeUnitLabel(double time, QWidget *parent) : QLabel(parent), time(time) {
    QString unitStr;
    QString timeStr = "0";

    for(const auto &unit : TIME_UNITS) {
        auto m = unit.multiplier();
        if (this->time >= m) {
            unitStr = unit.str();
            timeStr = QString::number(this->time/m);
        } else {
            break;
        }
    }
    this->setText(timeStr + unitStr);
}
