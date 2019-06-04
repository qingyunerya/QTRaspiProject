#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <wiringPi.h>
#include <softPwm.h>
namespace Ui {
class FirstWindow;
}

class FirstWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();
    void init();
    void init2();
    QTimer *timer;
    int index;
    int num;int num2;
private slots:
    void timerUpDate();

    void on_color_changed_button_clicked();

    void on_red_button_clicked();

    void on_green_button_clicked();

    void on_blue_button_clicked();

    void on_all_button_clicked();

    void on_color_faded_button_clicked();

private:
    Ui::FirstWindow *ui;
};

#endif // FIRSTWINDOW_H
