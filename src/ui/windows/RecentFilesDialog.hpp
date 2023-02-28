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
#ifndef MOTIV_RECENTFILESDIALOG_HPP
#define MOTIV_RECENTFILESDIALOG_HPP


#include <QDialog>

/**
 * @brief A dialog that displays an open button and previously opened trace files.
 *
 * On QDialog::Accept the reference supplied in the constructor is updated to the selected path.
 *
 * @code{.cpp}
 * QString myPath;
 * RecentFilesDialog dialog(&myPath);
 *
 * if (dialog.exec() == QDialog::Accepted)
 *     std::cout << "Path supplied: " << myPath << std::endl;
 * else
 *     std::cout << "No path supplied" << std::endl;
 * @endcode
 */
class RecentFilesDialog : public QDialog {
public:
    /**
     * @param dest variable to write the result to.
     */
    RecentFilesDialog(QString *dest);

private:
    QString *dest;
};


#endif //MOTIV_RECENTFILESDIALOG_HPP
