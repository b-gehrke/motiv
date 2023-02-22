#ifndef MOTIV_UTILS_HPP
#define MOTIV_UTILS_HPP

#include <QLayout>
#include <QWidget>
#include "src/models/communication/CommunicationKind.hpp"

/**
 * Resets a QLayout and deletes all child widgets.
 *
 * Source: https://stackoverflow.com/a/56966160
 *
 * @param apLayout layout to reset
 */
void resetLayout(QLayout *apLayout);

std::string communicationKindName(CommunicationKind kind);

std::string collectiveCommunicationOperationName(otf2::collective_type type);

#endif //MOTIV_UTILS_HPP
