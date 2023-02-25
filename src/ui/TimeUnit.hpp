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
#ifndef MOTIV_TIMEUNIT_HPP
#define MOTIV_TIMEUNIT_HPP

#include <QString>

#include "src/types.h"


/**
 * Represents possible units on the time scale.
 */
struct TimeUnit {
    enum Unit {
        NanoSecond,
        MicroSecond,
        MilliSecond,
        Second,
        Minute,
        Hour,
    };

    TimeUnit(Unit unit);
    /**
     * Construct TimeUnit from string.
     * @param unit SI time string (e.g. ns, μs, s, h)
     */
    TimeUnit(QString unit);

    /**
     * Turns TimeUnit into SI time format.
     * @return @ref Unit "Unit" as SI string
     */
    QString str() const;

    /**
     * @return value for conversion between base representation (ns) and other units.
     */
    double multiplier() const;

private:
    Unit unit;
};

/**
 * List of possible TimeUnits in ascending order.
 */
static const TimeUnit TIME_UNITS[] = {TimeUnit::NanoSecond, TimeUnit::MicroSecond,TimeUnit::MilliSecond,
                                      TimeUnit::Second, TimeUnit::Minute, TimeUnit::Hour};


#endif //MOTIV_TIMEUNIT_HPP
