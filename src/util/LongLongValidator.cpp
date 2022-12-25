#include "LongLongValidator.hpp"

LongLongValidator::LongLongValidator(qlonglong minimum, qlonglong maximum, QObject *parent)
        : QValidator(parent), m_min(minimum), m_max(maximum){}

LongLongValidator::LongLongValidator(QObject *parent)
        : LongLongValidator(std::numeric_limits<qlonglong>::min(),std::numeric_limits<qlonglong>::max(), parent){}

qlonglong LongLongValidator::bottom() const { return m_min; }

qlonglong LongLongValidator::top() const { return m_max; }

void LongLongValidator::setBottom(qlonglong minimum) {
    if(m_min==minimum)
        return;
    m_min=minimum;
    changed();
}

void LongLongValidator::setTop(qlonglong maximum) {
    if(m_max==maximum)
        return;
    m_max=maximum;
    changed();
}

void LongLongValidator::setRange(qlonglong minimum, qlonglong maximum) {
    setBottom(minimum);
    setTop(maximum);
}

QValidator::State LongLongValidator::validate(QString &input, int &) const {
    bool convertOk=false;
    qlonglong numInput = input.toLongLong(&convertOk);

    if(!convertOk)
        return QValidator::Invalid;
    if(numInput<m_min)
        return QValidator::Intermediate;
    if(numInput>m_max)
        return QValidator::Invalid;

    return QValidator::Acceptable;
}
