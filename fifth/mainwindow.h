#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <wiringPi.h>
#include <softPwm.h>
#include <QPalette>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *timer;
    int index1;
    int pressing;int pressed;int free;
    int pressing2;int pressed2;int free2;
    int count;
    int c1,c2,c3;
    int v1,v2,v3;
    QPalette palette;
    void init1();
    void init3();
    QTimer *timer1;
    int index;
    int num;int num2;
private slots:
    void timerUpDate();
    void init();
    void init2();
    void on_pushButton_view_clicked();
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
