#ifndef MOTIV_LONGLONGVALIDATOR_HPP
#define MOTIV_LONGLONGVALIDATOR_HPP

#include <QValidator>

class LongLongValidator : public QValidator {
    Q_OBJECT

public:
    LongLongValidator(qlonglong minimum, qlonglong maximum, QObject *parent = nullptr);

    explicit LongLongValidator(QObject *parent = nullptr);

    qlonglong bottom() const;
    qlonglong top() const;

    void setBottom(qlonglong minimum);

    void setTop(qlonglong maximum);

    void setRange(qlonglong minimum, qlonglong maximum);

    QValidator::State validate(QString &input, int&) const override;

private:
    qlonglong m_min;
    qlonglong m_max;

};

#endif //MOTIV_LONGLONGVALIDATOR_HPP
