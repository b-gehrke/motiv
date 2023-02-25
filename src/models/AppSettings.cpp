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
#include "AppSettings.hpp"

#define SET_AND_EMIT(key) \
    settings.setValue(#key, key##_); \
    Q_EMIT key##Changed(key##_);

AppSettings::AppSettings() {
    this->recentlyOpenedFiles_ = this->settings.value("recentlyOpenedFiles").toStringList();
}

const QStringList &AppSettings::recentlyOpenedFiles() const {
    return recentlyOpenedFiles_;
}

void AppSettings::recentlyOpenedFilesPush(const QString &newFile) {
    // Make sure most recent files are always at the back.
    recentlyOpenedFiles_.removeAll(newFile);
    recentlyOpenedFiles_.push_back(newFile);
    SET_AND_EMIT(recentlyOpenedFiles)
}

void AppSettings::recentlyOpenedFilesRemove(const QString &filePath) {
    recentlyOpenedFiles_.removeAll(filePath);
    SET_AND_EMIT(recentlyOpenedFiles)
}

void AppSettings::recentlyOpenedFilesClear() {
    this->recentlyOpenedFiles_.clear();
    SET_AND_EMIT(recentlyOpenedFiles)
}
