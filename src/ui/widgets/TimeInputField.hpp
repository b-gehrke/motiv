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
#ifndef MOTIV_TIMEINPUTFIELD_HPP
#define MOTIV_TIMEINPUTFIELD_HPP

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

#include "src/types.h"
#include "src/ui/TimeUnit.hpp"
#include "src/ui/TraceDataProxy.hpp"

/**
 * TimeInputField provides a combination of a QLabel, QLineEdit and QComboBox.
 *
 * This widget allows to control a TraceTime at different degrees of granularity.
 */
class TimeInputField : public QWidget {
    Q_OBJECT

public Q_SLOTS:
    void setTime(types::TraceTime newTime);

public: // constructors
    TimeInputField(QString labelText, TimeUnit timeResolution, types::TraceTime initialTime, QWidget *parent = nullptr);

public: // methods
    void setUpdateFunction(std::function<void (types::TraceTime)>);

private: // methods

private: // widgets
    QLabel *textLabel = nullptr;
    QLineEdit *lineEdit = nullptr;
    QComboBox *comboBox = nullptr;

private: // data
    QString text;
    TimeUnit resolution;

    /**
     * DO NOT set this manually. Always use setTime()!
     */
    types::TraceTime time;

    std::function<void (types::TraceTime)> updateFunction;
};


#endif //MOTIV_TIMEINPUTFIELD_HPP
