/*
 * Marvellous OTF2 Traces Interactive Visualizer (MOTIV)
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
#ifndef MOTIV_ABOUT_HPP
#define MOTIV_ABOUT_HPP

#include <QWidget>

#define LN "<br>"

class About : public QWidget {
public:
    explicit About(QWidget *parent = nullptr) : QWidget(parent) {
        this->setAttribute(Qt::WA_DeleteOnClose);

        auto topLayout = new QHBoxLayout;
        topLayout->setAlignment(Qt::AlignTop | Qt::AlignLeading);
        topLayout->setSizeConstraint(QLayout::SetFixedSize);
        this->setLayout(topLayout);

        QPixmap appIcon(":res/motiv.png");
        appIcon = appIcon.scaled(200, 200);
        auto appIconImage = new QLabel;
        appIconImage->setPixmap(appIcon);
        topLayout->addWidget(appIconImage);

        topLayout->addSpacing(20);

        QString string;
        QTextStream text(&string);
        text << "<b>Marvelous OTF2 Trace Interactive Visualizer</b>" << LN
             << "<i>Version " MOTIV_VERSION_STRING "</i>" << LN << LN
             << tr("Motiv is a free and open source application for viewing and analyzing OTF2 traces.") << LN << LN
             << "Copyright 2023 Motiv contributors" << LN
             << "<ul>"
             << "<li><a href=\"" MOTIV_SOURCE_URL "\">View source code</a></li>"
             << "<li><a href=\"" MOTIV_ISSUES_URL "\">Report issue</a></li>"
             << "</ul>";

        auto label = new QLabel(string, this);
        label->setWordWrap(true);
        label->setFixedWidth(400);
        label->setTextFormat(Qt::RichText);
        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
        label->setOpenExternalLinks(true);
        topLayout->addWidget(label);
    }
};

#endif //MOTIV_ABOUT_HPP
