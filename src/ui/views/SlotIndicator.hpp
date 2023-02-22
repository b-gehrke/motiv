#ifndef MOTIV_SLOTINDICATOR_HPP
#define MOTIV_SLOTINDICATOR_HPP


#include <QGraphicsRectItem>

#include "src/ui/TraceDataProxy.hpp"
#include "src/models/Slot.hpp"
#include "src/types.h"
#include "GenericIndicator.hpp"

class SlotIndicator : public GenericIndicator<Slot, QGraphicsRectItem> {
public: // constructors
    SlotIndicator(const QRectF &rect, Slot* representedSlot, QGraphicsItem *parent = nullptr);
};


#endif //MOTIV_SLOTINDICATOR_HPP
