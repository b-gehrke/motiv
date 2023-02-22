#ifndef MOTIV_CONSTANTS_HPP
#define MOTIV_CONSTANTS_HPP


namespace layers {
    const int Z_LAYER_HIGHLIGHTED_OFFSET = 20;
    const int Z_LAYER_P2P_COMMUNICATIONS = 100;
    const int Z_LAYER_COLLECTIVE_COMMUNICATIONS = 110;
    const int Z_LAYER_SLOTS_MIN_PRIORITY = 10;
    const int Z_LAYER_SLOTS_MAX_PRIORITY = Z_LAYER_SLOTS_MIN_PRIORITY + Z_LAYER_HIGHLIGHTED_OFFSET - 1;
    const int Z_LAYER_SELECTION = 200;
}

namespace colors {
    const QColor COLOR_SLOT_MPI = QColor::fromRgb(0xCDDC39);
    const QColor COLOR_SLOT_OPEN_MP = QColor::fromRgb(0xFF5722);
    const QColor COLOR_SLOT_PLAIN = QColor::fromRgb(0xBDBDBD);
    const QColor COLOR_COLLECTIVE_COMMUNICATION = QColor::fromRgb(0x42A5F5);
}

#endif //MOTIV_CONSTANTS_HPP
