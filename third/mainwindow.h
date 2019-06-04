#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int fd;
    int index;
    QTimer *timer;

    void adxl345_init(int fd);
    void adxl345_read_xyz(int fd);

private slots:

    void timerUpDate();
    void on_read_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
