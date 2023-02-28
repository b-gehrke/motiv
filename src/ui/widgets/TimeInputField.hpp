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

#include "src/types.hpp"
#include "src/ui/TimeUnit.hpp"
#include "src/ui/TraceDataProxy.hpp"

/**
 * TimeInputField provides a combination of a QLabel, QLineEdit and QComboBox.
 *
 * The QLabel displays an informational text, QLineEdit is a field that allows a double value as input,
 * and the QComboBox can be used to select a time unit.
 * Selecting a different time unit will automatically adjust the value in the input field.
 * The purpose of this widget is to control a TraceTime at different degrees of granularity.
 *
 * By default, the widget does only keep its internal state and does not modify any other variable.
 * In order to use the entered value you have to set an update function
 * using @ref setUpdateFunction(std::function<void (types::TraceTime)>) "setUpdateFunction(yourFunc)".
 *
 * @code{.cpp}
 * types::TraceTime myTime(0);
 * auto field = new TimeInputField("Start", TimeUnit::Second, TraceTime(0));
 * field->setUpdateFunction([&myTime](auto newStartTime) { myTime = newStartTime); });
 * @endcode
 */
class TimeInputField : public QWidget {
    Q_OBJECT

public Q_SLOTS:
    /**
     * @brief Sets the time
     *
     * The UI is updated afterwars to reflect the new time
     *
     * @param newTime The new time
     */
    void setTime(types::TraceTime newTime);

public: // constructors
    /**
     * Creates new TimeInputField.
     * @param labelText Informational text to display left of the input field
     * @param timeResolution Initial temporal resolution of the widget
     * @param initialTime Initial value to display
     * @param parent
     */
    TimeInputField(QString labelText, TimeUnit timeResolution, types::TraceTime initialTime, QWidget *parent = nullptr);

public: // methods
    /**
     * Set an update function that is called when a new value is entered.
     * See @ref TimeInputField "TimeInputField" for an example.
     */
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
