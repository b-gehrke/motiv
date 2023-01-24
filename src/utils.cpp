#include "utils.hpp"

void resetLayout(QLayout *apLayout) {
    QLayoutItem *vpItem;
    while ((vpItem = apLayout->takeAt(0)) != 0) {
        if (vpItem->layout()) {
            resetLayout(vpItem->layout());
            vpItem->layout()->deleteLater();
        }
        if (vpItem->widget()) {
            vpItem->widget()->deleteLater();
        }
        delete vpItem;
    }
}