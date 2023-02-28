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
#ifndef MOTIV_INFORMATIONDOCKELEMENTBASESTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKELEMENTBASESTRATEGY_HPP

#include "InformationDockElementStrategy.hpp"
#include "src/ui/widgets/TimeUnitLabel.hpp"

/**
 * @brief A generic InformationDockElementStrategy for specific TimedElements.
 *
 * This class abstracts a type check for selected elements. Derived classes can specify with the template parameter
 * for which type of element they visualise information. Derived classes can overwrite the updateView function and
 * get the selected element casted to their accepted type if it is of their accepted type.
 *
 * @tparam T Type of TimedElement derived strategies accept
 */
template<class T> requires std::is_base_of_v<TimedElement, T>
class InformationDockElementBaseStrategy : public InformationDockElementStrategy {
public:
    /**
     * @see QObject::tr()
     */
    static QString tr(const char *s, const char *c = nullptr, int n = -1) {
        return QObject::tr(s, c, n);
    }

public:
    /**
     * @brief Checks if the strategy is applicable for an element and returns the casted element if so.
     *
     * By default this function does a dynamic_cast to check whether the strategy is applicable to for the element. A
     * derived class can overwrite this behaviour if there are other options to identify the runtime type.
     *
     * @param t The newly selected element.
     * @return The selected element casted to T if the strategy accepts the element or nullptr if it does not
     */
    virtual T *applicable(TimedElement *t) { return dynamic_cast<T *>(t); }

    /**
     * @copydoc InformationDockElementStrategy::setup(QFormLayout*)
     */
    void setup(QFormLayout *layout) override;

    /**
     * @brief Updates the view
     *
     * Derived classes should overwrite this function but call the base implementation as it updates the time fields.
     * The element pointer is guaranteed to be not null.
     *
     * @param layout The layout of the detailed window pane
     * @param element The newly selected element
     */
    virtual void updateView(QFormLayout *layout, T *element);

    /**
     * @copydoc InformationDockElementStrategy::setup
     */
    bool update(QFormLayout *layout, TimedElement *element) override;

    /**
     * @copydoc InformationDockElementStrategy::title()
     */
    std::string title() override;

protected:
    TimeUnitLabel *startField = nullptr; /**< The start field displaying the start time of the element*/
    TimeUnitLabel *endField = nullptr; /**< The end field displaying the end time of the element*/
    TimeUnitLabel *runtimeField = nullptr; /**< The runtime field displaying the runtime of the element*/
};


#endif //MOTIV_INFORMATIONDOCKELEMENTBASESTRATEGY_HPP
