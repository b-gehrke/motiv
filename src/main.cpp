#include "src/ui/MainWindow.hpp"

#include <QApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QIODeviceBase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Motiv");
    QApplication::setApplicationVersion("0.1.0" /* TODO macro via CMakeLists.txt*/);

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

    MainWindow mainWindow(filepath);
    mainWindow.show();

    return app.exec();
}
