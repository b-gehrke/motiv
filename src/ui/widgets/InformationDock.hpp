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
#ifndef MOTIV_INFORMATIONDOCK_HPP
#define MOTIV_INFORMATIONDOCK_HPP


#include "TimeUnitLabel.hpp"
#include "src/ui/TraceDataProxy.hpp"
#include "src/ui/widgets/infostrategies/InformationDockElementStrategy.hpp"
#include <QLabel>
#include <QFormLayout>
#include <QDockWidget>

class InformationDock : public QDockWidget {
Q_OBJECT
public:
    explicit InformationDock(QWidget *parent = nullptr);

public:
    void addElementStrategy(InformationDockElementStrategy *s);

public:
Q_SIGNALS:

    void zoomToWindow(types::TraceTime from, types::TraceTime to);

public Q_SLOTS:

    void zoomIntoViewPressed();

    void setElement(TimedElement *element);

protected:
    virtual void updateView();

private: // fields
    TimedElement *element_ = nullptr;

private:
    QWidget *child = nullptr;
    QFormLayout *childLayout = nullptr;

    std::vector<std::pair<QWidget*, InformationDockElementStrategy*>> strategies_ {};
};


#endif //MOTIV_INFORMATIONDOCK_HPP
