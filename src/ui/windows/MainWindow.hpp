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
#ifndef MOTIV_MAINWINDOW_HPP
#define MOTIV_MAINWINDOW_HPP


#include <QMainWindow>

#include "src/ui/widgets/TimeInputField.hpp"
#include "src/ui/TraceDataProxy.hpp"
#include "src/ReaderCallbacks.hpp"
#include "src/ui/widgets/TraceOverviewDock.hpp"
#include "src/ui/widgets/InformationDock.hpp"
#include "src/ui/widgets/License.hpp"
#include "src/ui/widgets/Help.hpp"
#include "src/ui/widgets/About.hpp"

/**
 * @brief The main window of the application.
 *
 * This class sets up and connects all components and menu bars as well as loading the trace.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public: // constructors
    /**
     * @brief Creates a new instance of the MainWindow class.
     *
     * @param filepath Path to trace file. If omitted the user is promted for it.
     */
    explicit MainWindow(QString filepath = QString());
    ~MainWindow() override;

public: Q_SIGNALS:
    // TODO

public Q_SLOTS:
    /**
     * @brief Resets the zoom to show the entire trace.
     */
    void resetZoom();

    /**
     * @brief Opens and shows the FilterPopup
     */
    void openFilterPopup();

    /**
     * @brief Asks for a new trace file and opens the trace
     */
    void openNewTrace();

private: // methods
    void createMenus();
    void createToolBars();
    void createDockWidgets();
    void createCentralWidget();

    QString promptFile();
    void loadTrace();
    void loadSettings();
    void openNewWindow(QString path);

private: // widgets
    QToolBar *topToolbar = nullptr;
    QToolBar *bottomToolbar = nullptr;

    InformationDock *information = nullptr;
    TraceOverviewDock *traceOverview = nullptr;

    TimeInputField *startTimeInputField = nullptr;
    TimeInputField *endTimeInputField = nullptr;

    License *licenseWindow = nullptr;
    Help *helpWindow = nullptr;
    About *aboutWindow = nullptr;

private: // properties
    QString filepath;
    TraceDataProxy *data = nullptr;

    otf2::reader::reader *reader = nullptr;
    ReaderCallbacks *callbacks = nullptr;

    ViewSettings *settings = nullptr;
};


#endif //MOTIV_MAINWINDOW_HPP
