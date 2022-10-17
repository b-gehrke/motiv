#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <otf2xx/otf2.hpp>

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

    void onButtonClicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
