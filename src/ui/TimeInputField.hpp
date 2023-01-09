#ifndef MOTIV_TIMEINPUTFIELD_HPP
#define MOTIV_TIMEINPUTFIELD_HPP

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

#include "src/types.h"
#include "TimeUnit.hpp"

/**
 * TimeInputField provides a combination of a QLabel, QLineEdit and QComboBox.
 *
 * This widget allows to control a TraceTime at different degrees of granularity.
 */
class TimeInputField : public QWidget {
    Q_OBJECT

public: // constructors
    TimeInputField(QString labelText, TimeUnit timeResolution, types::TraceTime initialTime, QWidget *parent = nullptr);

public: // methods

private: // widgets
    QLabel *textLabel = nullptr;
    QLineEdit *lineEdit = nullptr;
    QComboBox *comboBox = nullptr;

private: // data
    QString text;
    TimeUnit resolution;
    types::TraceTime time;
};


#endif //MOTIV_TIMEINPUTFIELD_HPP
