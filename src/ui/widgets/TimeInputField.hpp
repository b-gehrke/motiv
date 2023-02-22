#ifndef MOTIV_TIMEINPUTFIELD_HPP
#define MOTIV_TIMEINPUTFIELD_HPP

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

#include "src/types.h"
#include "src/ui/TimeUnit.hpp"
#include "src/ui/TraceDataProxy.hpp"

/**
 * TimeInputField provides a combination of a QLabel, QLineEdit and QComboBox.
 *
 * This widget allows to control a TraceTime at different degrees of granularity.
 */
class TimeInputField : public QWidget {
    Q_OBJECT

public Q_SLOTS:
    void setTime(types::TraceTime newTime);

public: // constructors
    TimeInputField(QString labelText, TimeUnit timeResolution, types::TraceTime initialTime, QWidget *parent = nullptr);

public: // methods
    void setUpdateFunction(std::function<void (types::TraceTime)>);

private: // methods

private: // widgets
    QLabel *textLabel = nullptr;
    QLineEdit *lineEdit = nullptr;
    QComboBox *comboBox = nullptr;

private: // data
    QString text;
    TimeUnit resolution;

    /**
     * DO NOT set this manually. Always use setTime()!
     */
    types::TraceTime time;

    std::function<void (types::TraceTime)> updateFunction;
};


#endif //MOTIV_TIMEINPUTFIELD_HPP