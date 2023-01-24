#include "ViewSettings.hpp"

int ViewSettings::getZoomQuotient() const {
    return zoomFactor;
}

void ViewSettings::setZoomFactor(int zoomFactor) {
    ViewSettings::zoomFactor = zoomFactor;
}

SlotKind ViewSettings::getFilter() const {
    return filter;
}

void ViewSettings::setFilter(SlotKind filter) {
    ViewSettings::filter = filter;
}
