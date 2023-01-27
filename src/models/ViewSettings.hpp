#ifndef MOTIV_VIEWSETTINGS_HPP
#define MOTIV_VIEWSETTINGS_HPP

#include "src/models/slot.hpp"
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
