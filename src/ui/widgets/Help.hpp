/*
 * Marvelous OTF2 Traces Interactive Visualizer (MOTIV)
 * Copyright (C) 2023 Florian Gallrein, Björn Gehrke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MOTIV_HELP_HPP
#define MOTIV_HELP_HPP

#include <QFile>
#include <QTextEdit>

/**
 * A widget which provides users with information about the various views and controls
 * available in the application.
 */
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
