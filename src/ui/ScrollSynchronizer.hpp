#ifndef MOTIV_SCROLLSYNCHRONIZER_HPP
#define MOTIV_SCROLLSYNCHRONIZER_HPP


#include <QAbstractScrollArea>

/**
 * Synchronizes the scroll state of two or more widgets that inherit from QAbstractScrollArea.
 */
class ScrollSynchronizer : QObject {
public:
    explicit ScrollSynchronizer(QObject *parent = nullptr);

public:
    void addWidget(QAbstractScrollArea *widget);

private:
    QList<QAbstractScrollArea *> widgets;
};


#endif //MOTIV_SCROLLSYNCHRONIZER_HPP
