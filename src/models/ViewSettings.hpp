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
#ifndef MOTIV_VIEWSETTINGS_HPP
#define MOTIV_VIEWSETTINGS_HPP

#include "src/models/Slot.hpp"
#include "Filter.hpp"

#define SETTINGS_DEFAULT_ZOOM_QUOTIENT 25

/**
 * @brief The ViewSettings class encapsulates settings for the main view.
 *
 * It includes a filter to control which events are displayed and a zoom factor to control
 * the level of detail in the visualization.
 */
class ViewSettings {
public:

    /**
     * @brief Returns the current filter.
     * @return A Filter object representing the current filter.
     */
    [[nodiscard]] Filter getFilter() const;

    /**
     * @brief Returns the reciprocal of the current zoom factor.
     *
     * For example, if the zoom view is zoomed to show 1/50=2%, this function will return 50.
     * @return An integer representing the reciprocal of the current zoom factor.
     */
    [[nodiscard]] int getZoomQuotient() const;

    /**
     * @brief Sets the current filter.
     * @param filter A Filter object representing the new filter.
     */
    void setFilter(Filter filter);

    /**
     * @brief Sets the current zoom factor.
     *
     * The zoom factor defines how much of the actual trace is shown.
     * It is set as the reciprocal. For example, if the view is
     * zoom to show only 2%=1/50 of the whole view, the zoom factor is 50
     *
     * @param zoomFactor An integer representing the new zoom factor.
     */
    void setZoomFactor(int zoomFactor);

private:
    /**
     * Backing field for the current zoom factor.
     */
    int zoomFactor_ = SETTINGS_DEFAULT_ZOOM_QUOTIENT;
    /**
     * Backing field for the current filter.
     * */
    Filter filter_;
};


#endif //MOTIV_VIEWSETTINGS_HPP
