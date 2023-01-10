#ifndef MOTIV_UTILS_H
#define MOTIV_UTILS_H

#include <QLayout>
#include <QWidget>

/**
 * Resets a QLayout and deletes all child widgets.
 *
 * Source: https://stackoverflow.com/a/56966160
 *
 * @param apLayout layout to reset
 */
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


#endif //MOTIV_UTILS_H
