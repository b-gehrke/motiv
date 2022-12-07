#include "License.hpp"

#include <QFile>
#include <QLabel>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QTextStream>

using namespace view;

License::License(QWidget *parent) {
    auto layout = new QGridLayout(this);
    setLayout(layout);

    QFile licenseFile(":text/COPYING");
    if (!licenseFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("license file could not be opened");
        return;
    }

    QTextStream licenseTextStream(&licenseFile);
    QString licenseText = licenseTextStream.readAll();
    licenseFile.close();

    auto textField = new QPlainTextEdit(licenseText, this);
    textField->setReadOnly(true);
    layout->addWidget(textField);
}
