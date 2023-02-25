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
#ifndef MOTIV_INFORMATIONDOCKELEMENTBASESTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKELEMENTBASESTRATEGY_HPP

#include "InformationDockElementStrategy.hpp"
#include "src/ui/widgets/TimeUnitLabel.hpp"

template<class T> requires std::is_base_of_v<TimedElement, T>
class InformationDockElementBaseStrategy : public InformationDockElementStrategy {
public:
    static QString tr(const char *s, const char *c = nullptr, int n = -1) {
        return QObject::tr(s, c, n);
    }

public:
    virtual T *applicable(TimedElement *t) { return dynamic_cast<T *>(t); }

    void setup(QFormLayout *layout) override;

    virtual void updateView(QFormLayout *layout, T *element);

    bool update(QFormLayout *layout, TimedElement *element) override;

    std::string title() override;

protected:
    TimeUnitLabel *startField = nullptr;
    TimeUnitLabel *endField = nullptr;
    TimeUnitLabel *runtimeField = nullptr;
};


#endif //MOTIV_INFORMATIONDOCKELEMENTBASESTRATEGY_HPP
