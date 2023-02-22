#ifndef MOTIV_HELP_HPP
#define MOTIV_HELP_HPP

#include <QFile>
#include <QTextEdit>

class Help : public QTextEdit {
public:
    explicit Help(QWidget *parent = nullptr) : QTextEdit(parent) {
        QFile helpFile(":res/help.md");
        if (!helpFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug("help file could not be opened");
            return;
        }

        QTextStream helpTextStream(&helpFile);
        QString helpText = helpTextStream.readAll();
        helpFile.close();

        this->setReadOnly(true);
        this->setMarkdown(helpText);
        this->setWindowTitle(tr("Help"));
    }
};

#endif //MOTIV_HELP_HPP
