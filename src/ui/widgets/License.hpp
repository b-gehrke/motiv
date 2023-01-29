#ifndef MOTIV_LICENSE_HPP
#define MOTIV_LICENSE_HPP

#include <QFile>
#include <QTextEdit>

class License : public QTextEdit {
public:
    explicit License(QWidget *parent = nullptr) : QTextEdit(parent) {
        QFile licenseFile(":res/gpl-3.0.html");
        if (!licenseFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug("license file could not be opened");
            return;
        }

        QTextStream licenseTextStream(&licenseFile);
        QString licenseText = licenseTextStream.readAll();
        licenseFile.close();

        this->setReadOnly(true);
        this->setHtml(licenseText);
    }
};

#endif //MOTIV_LICENSE_HPP
