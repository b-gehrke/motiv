#ifndef MOTIV_COLORS_HPP
#define MOTIV_COLORS_HPP

#include <QColor>

// This is not a nice solution but C++ does only allow
// integral type for enums.
namespace Color {
    static const QColor Waiting("red");
    static const QColor Running("green");
}

#endif // MOTIV_COLORS_HPP