#include "src/ui/windows/MainWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    // TODO Make this more sophisticated
    QString path;
    if (argc > 1) {
        auto arg = QString::fromUtf8(argv[1]);
        if (!arg.endsWith(".otf2")) {
            std::cout << "Invalid path: " << argv[1] << std::endl;
            return EXIT_FAILURE;
        }
        path = arg;
    }
    QApplication app(argc, argv);

    MainWindow mainWindow(path, nullptr);
    mainWindow.show();

    return app.exec();
}
