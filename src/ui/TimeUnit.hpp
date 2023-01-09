#ifndef MOTIV_TIMEUNIT_HPP
#define MOTIV_TIMEUNIT_HPP

#include <QString>

#include "src/types.h"


/**
 * Represents possible units on the time scale.
 */
struct TimeUnit {
    enum Unit {
        NanoSecond,
        MicroSecond,
        MilliSecond,
        Second,
        Minute,
        Hour,
    };

    TimeUnit(Unit unit);
    TimeUnit(QString unit);

    QString str() const;

    /**
     * @return value for conversion between base representation (ns) and other units.
     */
    double multiplier() const;

private:
    Unit unit;
};

/**
 * List of possible TimeUnits in ascending order.
 */
static const TimeUnit TIME_UNITS[] = {TimeUnit::NanoSecond, TimeUnit::MicroSecond,TimeUnit::MilliSecond,
                                      TimeUnit::Second, TimeUnit::Minute, TimeUnit::Hour};


#endif //MOTIV_TIMEUNIT_HPP
