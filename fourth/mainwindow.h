#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QPen>
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCore/qmath.h>
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
    int x,y,z;
    int move;
    int vx[150],vy[150],vz[150];
    QTimer *timer;
    QTimer *ani_timer;
    void paintEvent(QPaintEvent *event);
    void adxl345_init(int fd);
    void adxl345_read_xyz(int fd);
private slots:
    void ani_timer_tick();
    void timerUpDate();
    void on_read_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
