#ifndef FIFTHWINDOW_H
#define FIFTHWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <wiringPi.h>
#include <softPwm.h>
#include <QPalette>
namespace Ui {
class FifthWindow;
}

class FifthWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FifthWindow(QWidget *parent = 0);
    ~FifthWindow();
    QTimer *timer;
    int index;
    int pressing;int pressed;int free;
    int pressing2;int pressed2;int free2;
    int count;
    int c1,c2,c3;
    int v1,v2,v3;
    QPalette palette;
private slots:
    void timerUpDate();
    void init();
    void init2();
    void on_pushButton_view_clicked();

private:
    Ui::FifthWindow *ui;
};

#endif // FIFTHWINDOW_H
