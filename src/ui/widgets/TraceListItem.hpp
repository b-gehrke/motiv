#ifndef MOTIV_TRACELISTITEM_HPP
#define MOTIV_TRACELISTITEM_HPP

#include <QPen>
#include <QWidget>
#include "src/models/slot.hpp"
#include "src/models/trace.hpp"


    class TraceListItem : public QWidget {
    public:
        explicit TraceListItem(QString name, Range<Slot> slots, long long min, long long max, const QWidget *parent);

        QSize sizeHint() const override
        {
            return QSize(400, 200);
        }

        QSize minimumSizeHint() const override
        {
            return QSize(100, 50);
        }

    Q_SIGNALS:
        void selectionUpdated();

    protected:
        void paintEvent(QPaintEvent *event) override;

    private: // data
        const QString name;
        const Range<Slot> slots;
        const long long max;
        const long long min;
    private:
        QBrush brush;
        QPen pen;
    };

#endif //MOTIV_TRACELISTITEM_HPP
