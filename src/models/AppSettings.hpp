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
#ifndef MOTIV_APPSETTINGS_HPP
#define MOTIV_APPSETTINGS_HPP


#include <QSettings>

/**
 * @brief Singleton holding persistent information
 */
class AppSettings : QObject {
Q_OBJECT
private:
    AppSettings();

public:
    /**
     * @return instance of AppSettings
     */
    static AppSettings &getInstance() {
        static AppSettings instance;
        return instance;
    }

    // Do not implement copy and copy assignment constructor.
    AppSettings(AppSettings const &) = delete;
    void operator=(AppSettings const &) = delete;


    /**
     * @brief Returns the recently opened files
     * @return The recently opened files
     */
    [[nodiscard]] const QStringList &recentlyOpenedFiles() const;

    /**
     * @brief Pushes a new file to the recently opened files list
     *
     * After the file is added to the list is saved.
     *
     * @param newFile The new opened file
     */
    void recentlyOpenedFilesPush(const QString &newFile);

    /**
     * @brief Removes a file from the recently opened files list
     *
     * After the file is removed the list is saved
     *
     * @param filePath The file to be removed
     */
    void recentlyOpenedFilesRemove(const QString &filePath);

    /**
     * @brief Clears the recently opened files list
     *
     * After the list is cleared it is saved
     */
    void recentlyOpenedFilesClear();

public: Q_SIGNALS:
    /**
     * @brief Signals a change in the recently opened files
     */
    void recentlyOpenedFilesChanged(QStringList);

private:
    QSettings settings;
    QString leastRecentDirectory_;
    QStringList recentlyOpenedFiles_;
};


#endif //MOTIV_APPSETTINGS_HPP
