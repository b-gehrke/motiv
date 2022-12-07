#include <QHBoxLayout>
#include <QLabel>
#include "TraceListItem.hpp"

using namespace view;

TraceListItem::TraceListItem(const QString &name, const Range<Slot> &slots, const QWidget &parent) {
    auto layout = new QHBoxLayout(this);
    setLayout(layout);

    auto nameLabel = new QLabel(name, this);
    layout->addWidget(nameLabel);

    for (auto const &slot : slots) {
        auto regionName = slot.region.name().str();
        auto regionLabel = new QLabel(QString::fromStdString(regionName), this);
        layout->addWidget(regionLabel);
    }
}
