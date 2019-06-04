#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
namespace Ui {
class ThirdWindow;
}

class ThirdWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ThirdWindow(QWidget *parent = 0);
    ~ThirdWindow();
    int fd;
    int index;
    QTimer *timer;

    void adxl345_init(int fd);
    void adxl345_read_xyz(int fd);

private slots:

    void timerUpDate();
    void on_read_button_clicked();

private:
    Ui::ThirdWindow *ui;
};

#endif // THIRDWINDOW_H
