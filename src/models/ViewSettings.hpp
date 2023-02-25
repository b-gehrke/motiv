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
#ifndef MOTIV_VIEWSETTINGS_HPP
#define MOTIV_VIEWSETTINGS_HPP

#include "src/models/Slot.hpp"
#include "Filter.hpp"

#define SETTINGS_DEFAULT_ZOOM_QUOTIENT 25

class ViewSettings {
public:

public:
    [[nodiscard]] Filter getFilter() const;
    /**
     * Returns the reciprocal of a zoom factor
     *
     * E.g. 50 represents a 1/50 = 2% zoom
     * @return
     */
    [[nodiscard]] int getZoomQuotient() const;


    void setFilter(Filter filter);
    void setZoomFactor(int zoomFactor);

private:
    int zoomFactor_ = SETTINGS_DEFAULT_ZOOM_QUOTIENT;
    Filter filter_;
};


#endif //MOTIV_VIEWSETTINGS_HPP
