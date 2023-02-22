#ifndef MOTIV_TIMEUNITLABEL_HPP
#define MOTIV_TIMEUNITLABEL_HPP


#include <QLabel>
#include "src/types.h"

class TimeUnitLabel : public QLabel {
    Q_OBJECT

public:
    explicit TimeUnitLabel(double time, QWidget *parent = nullptr);

    void setTime(double time);
    [[nodiscard]] double getTime() const;

    void updateView();

private:
    double time;
};


#endif //MOTIV_TIMEUNITLABEL_HPP
