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
#include "TimeUnit.hpp"

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

double TimeUnit::multiplier() const {
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