#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <random>
#include <utility>
#include "TraceListItem.hpp"


TraceListItem::TraceListItem(QString name, const Range<Slot> slots, const long long min, const long long max, const QWidget *parent)
: name(std::move(name)), slots(slots), min(min), max(max) {

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::blue);
//    setBackgroundRole(QPalette::Base);
//    setAutoFillBackground(true);
}

void TraceListItem::paintEvent(QPaintEvent *event) {
    auto scope = max - min;
    auto textPainter = QPainter(this);
    // TODO determine size
    textPainter.drawText(10, height()/2+5, name);

    auto painter = QPainter(this);
    textPainter.setBrush(brush);
    textPainter.setPen(pen);

    auto wid = width() - 100;

    for (auto const &slot : slots) {
        auto start = slot.start.count();
        auto end = slot.end.count();

        auto fraction = (end - start)/double(scope);

        QPainterPath path;

        auto recWidth = fraction*wid;
        if (recWidth < 10) recWidth = 10;

        auto rectangle = QRect((start - min)/scope+100, 0, recWidth, height());
        path.addRect(rectangle);

        auto color = slot.region.name().str().starts_with("MPI_") ? "green" : "red";
        painter.fillPath(path, QColor(color));
        painter.drawPath(path);
    }
}
