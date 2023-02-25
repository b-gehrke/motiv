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
#ifndef MOTIV_FILTERPOPUP_HPP
#define MOTIV_FILTERPOPUP_HPP


#include <QDialog>
#include <QGroupBox>
#include <QCheckBox>
#include "src/models/Filter.hpp"

class FilterPopup : public QDialog {
Q_OBJECT

public: // constructors
    /**
     * Creates a new instance of this modal popup.
     * @param filter The current filter object
     * @param parent See QDialog::QDialog(QWidget*, Qt::WindowFlags)
     * @param f See QDialog::QDialog(QWidget*, Qt::WindowFlags)
     */
    explicit FilterPopup(const Filter &filter, QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags());

public: // methods

public Q_SLOTS:
    /**
     * Applies the changes made in the UI to @c filter_
     */
    void updateFilter();

public: Q_SIGNALS:
    /**
     * Signals the filter was changes
     */
    void filterChanged(Filter);

private: // fields
    Filter filter_;

private: // widgets
    QCheckBox *mpiSlotKindCheckBox = nullptr;
    QCheckBox *openMpSlotKindCheckBox = nullptr;
    QCheckBox *plainSlotKindCheckBox = nullptr;
};


#endif //MOTIV_FILTERPOPUP_HPP
