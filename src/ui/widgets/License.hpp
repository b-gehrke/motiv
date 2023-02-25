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
#ifndef MOTIV_LICENSE_HPP
#define MOTIV_LICENSE_HPP

#include <QFile>
#include <QTextEdit>

/**
 * A widget showcasing displaying license information about this software.
 */
class License : public QTextEdit {
public:
    /**
     * Creates new instance of License widget.
     * It is recommended to pass nullptr as @p parent so that it shows as modal window.
     * Do not forget to call `show()` on the constructed object if parent is nullptr.
     *
     * @param parent
     */
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
        this->setWindowTitle(tr("License"));
    }
};

#endif //MOTIV_LICENSE_HPP
