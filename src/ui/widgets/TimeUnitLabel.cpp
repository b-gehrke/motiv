/*
 * Marvelous OTF2 Traces Interactive Visualizer (MOTIV)
 * Copyright (C) 2023 Florian Gallrein, Björn Gehrke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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

