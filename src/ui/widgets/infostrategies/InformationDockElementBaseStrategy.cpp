/*
 * Marvellous OTF2 Traces Interactive Visualizer (MOTIV)
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
#include "InformationDockElementBaseStrategy.hpp"
#include "src/models/Slot.hpp"
#include "src/models/Trace.hpp"

template<class T> requires std::is_base_of_v<TimedElement, T>
void InformationDockElementBaseStrategy<T>::setup(QFormLayout *layout)  {
    startField = new TimeUnitLabel(0);
    endField = new TimeUnitLabel(0);
    runtimeField = new TimeUnitLabel(0);


    layout->addRow(tr("Start:"), startField);
    layout->addRow(tr("End:"), endField);
    layout->addRow(tr("Runtime:"), runtimeField);
}

template<class T> requires std::is_base_of_v<TimedElement, T>
void InformationDockElementBaseStrategy<T>::updateView(QFormLayout *layout, T *element) {
    if (!element) return;

    auto start = static_cast<double>(element->getStartTime().count());
    auto end = static_cast<double>(element->getEndTime().count());
    auto runtime = static_cast<double>(element->getDuration().count());

    startField->setTime(start);
    endField->setTime(end);
    runtimeField->setTime(runtime);
}

template<class T>
requires std::is_base_of_v<TimedElement, T>bool
InformationDockElementBaseStrategy<T>::update(QFormLayout *layout, TimedElement *element) {
    T *t = applicable(element);
    if (t) {
        updateView(layout, t);
    }

    return t;
}

template<class T>
requires std::is_base_of_v<TimedElement, T>std::string InformationDockElementBaseStrategy<T>::title() {
    return typeid(T).name();
}

template class InformationDockElementBaseStrategy<Slot>;
template class InformationDockElementBaseStrategy<Trace>;
template class InformationDockElementBaseStrategy<Communication>;
template class InformationDockElementBaseStrategy<CollectiveCommunicationEvent>;
