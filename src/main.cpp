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
#include <QApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QIODeviceBase>

#include "src/ui/windows/MainWindow.hpp"
#include "src/ui/windows/RecentFilesDialog.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Motiv");
    QApplication::setApplicationVersion(MOTIV_VERSION_STRING);
    QApplication::setWindowIcon(QIcon(":/res/motiv.png"));

    // Load an application style
    QFile styleFile( ":/res/style.qss" );
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    QString style( styleFile.readAll() );
    app.setStyleSheet( style );

    QCommandLineParser parser;
    parser.setApplicationDescription("Visualizer for OTF2 trace files");

    QCommandLineOption helpOption = parser.addHelpOption();
    QCommandLineOption versionOption = parser.addVersionOption();
    parser.addPositionalArgument("file", QCoreApplication::translate("main", "filepath of the .otf2 trace file to open"), "[file]");
    parser.process(app);

    // Early return if help or version is shown
    if (parser.isSet(helpOption) || parser.isSet(versionOption)) {
        return EXIT_SUCCESS;
    }

    QStringList positionalArguments = parser.positionalArguments();
    QString filepath;
    if (!positionalArguments.isEmpty()) {
        filepath = positionalArguments.first();
    }

    RecentFilesDialog recentFilesDialog(&filepath);
    if(!filepath.isEmpty() || recentFilesDialog.exec() == QDialog::Accepted) {
        auto mainWindow = new MainWindow(filepath);
        mainWindow->show();
    } else {
        app.quit();
        return EXIT_SUCCESS;
    }

    return app.exec();
}
