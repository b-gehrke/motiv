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
#ifndef MOTIV_INFORMATIONDOCKELEMENTSTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKELEMENTSTRATEGY_HPP

#include "src/models/TimedElement.hpp"

#include <QFormLayout>

/**
 * @brief A base class for strategies for the InformationDock to show information about a TimedElement.
 */
class InformationDockElementStrategy {
public:
    /**
     * @brief Sets up the QFormLayout
     *
     * In derived classes this function should be overwritten and fields and rows should be added to the form layout.
     *
     * @param layout The layout of the detailed window pane
     */
    virtual void setup(QFormLayout*) { };

    /**
     * @brief Updates the view to show details about a newly selected element
     *
     * In derived classes this function should be overwritten and update the fields initialized in the setup call. If
     * the strategy cannot handle the newly selected element it should reject the update by returning false. If it does
     * so it should not change the form layout or the selected element.
     *
     * @param layout The layout of the detailed window pane
     * @param element The newly selected element
     *
     * @return Whether the strategy can handle the selected item and has performed an update.
     */
    virtual bool update(QFormLayout*, TimedElement*) { return false; };

    /**
     * @brief Returns the title the information dock should show
     * @return The title for the information dock should show
     */
    virtual std::string title() { return ""; }
};

#endif //MOTIV_INFORMATIONDOCKELEMENTSTRATEGY_HPP
