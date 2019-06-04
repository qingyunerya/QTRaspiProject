#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <wiringPi.h>
#include <softPwm.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = 0);
    ~SecondWindow();
    QTimer *timer;
    QSerialPort *serial;

private slots:
    void Read_Data();

    void timerUpDate();

    void on_pushButton_send_clicked();

    void on_pushButton_open_clicked();

private:
    Ui::SecondWindow *ui;
};

#endif // SECONDWINDOW_H
