#ifndef MOTIV_VIEWSETTINGS_HPP
#define MOTIV_VIEWSETTINGS_HPP

#include "src/models/slot.hpp"

#define SETTINGS_DEFAULT_ZOOM_QUOTIENT 25
#define SETTINGS_DEFAULT_FILTER ((SlotKind) (SlotKind::MPI | SlotKind::OpenMP | SlotKind::Plain))

class ViewSettings {
public:

public:
    [[nodiscard]] SlotKind getFilter() const;
    /**
     * Returns the reciprocal of a zoom factor
     *
     * E.g. 50 represents a 1/50 = 2% zoom
     * @return
     */
    [[nodiscard]] int getZoomQuotient() const;


    void setFilter(SlotKind filter);
    void setZoomFactor(int zoomFactor);

private:
    int zoomFactor = SETTINGS_DEFAULT_ZOOM_QUOTIENT;
    SlotKind filter = SETTINGS_DEFAULT_FILTER;
};


#endif //MOTIV_VIEWSETTINGS_HPP
