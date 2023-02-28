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
#ifndef MOTIV_OTF2FILEDIALOG_HPP
#define MOTIV_OTF2FILEDIALOG_HPP


#include <QFileDialog>

/**
 * @brief Wrapper around @ref QFileDialog "QFileDialog" that displays files with a otf2-file ending only.
 *
 * Besides, it checks the history for the last file opened, and shows the according directory.
 * If the history is empty, the home directory is shown instead.
 */
class Otf2FileDialog : public QFileDialog {
    Q_OBJECT
public:
    /**
     * See Qt documentation for QFileDialog
     * @param parent The parent QWidget
     */
    explicit Otf2FileDialog(QWidget *parent = nullptr);
};


#endif //MOTIV_OTF2FILEDIALOG_HPP
