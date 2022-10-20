#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include "src/models/trace.hpp"

#include <QMainWindow>
#undef foreach

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openTrace();

    void loadTrace();
    void showTrace(otf2::chrono::time_point start, otf2::chrono::time_point end);

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Trace> trace;
};


#endif // MAINWINDOW_H
