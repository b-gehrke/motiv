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

class MainWindow : public QMainWindow {
    Q_OBJECT

public: // constructors
    MainWindow(QString filepath = QString());
    ~MainWindow() override;

public: // methods
    void setFilepath(QString newFilepath);

public: Q_SIGNALS:
    // TODO

public Q_SLOTS:
    void resetZoom();
    void openFilterPopup();
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
