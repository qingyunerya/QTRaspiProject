#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <wiringPi.h>
#include <softPwm.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init1();
    void init3();
    QTimer *timer1;
    int index;
    int num;int num2;
private slots:
    void timerUpDate1();

    void on_color_changed_button_clicked();

    void on_red_button_clicked();

    void on_green_button_clicked();

    void on_blue_button_clicked();

    void on_all_button_clicked();

    void on_color_faded_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
