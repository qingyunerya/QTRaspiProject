#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    index=0;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->setInterval(1000);
    fd=wiringPiI2CSetup(0x53);
    adxl345_init(fd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerUpDate()
{
    adxl345_read_xyz(fd);
}

void MainWindow::adxl345_init(int fd)
{
    wiringPiI2CWriteReg8(fd, 0x31, 0x0b);
    wiringPiI2CWriteReg8(fd, 0x2d, 0x08);
//	wiringPiI2CWriteReg8(fd, 0x2e, 0x00);
    wiringPiI2CWriteReg8(fd, 0x1e, 0x00);
    wiringPiI2CWriteReg8(fd, 0x1f, 0x00);
    wiringPiI2CWriteReg8(fd, 0x20, 0x00);

    wiringPiI2CWriteReg8(fd, 0x21, 0x00);
    wiringPiI2CWriteReg8(fd, 0x22, 0x00);
    wiringPiI2CWriteReg8(fd, 0x23, 0x00);

    wiringPiI2CWriteReg8(fd, 0x24, 0x01);
    wiringPiI2CWriteReg8(fd, 0x25, 0x0f);
    wiringPiI2CWriteReg8(fd, 0x26, 0x2b);
    wiringPiI2CWriteReg8(fd, 0x27, 0x00);

    wiringPiI2CWriteReg8(fd, 0x28, 0x09);
    wiringPiI2CWriteReg8(fd, 0x29, 0xff);
    wiringPiI2CWriteReg8(fd, 0x2a, 0x80);
    wiringPiI2CWriteReg8(fd, 0x2c, 0x0a);
    wiringPiI2CWriteReg8(fd, 0x2f, 0x00);
    wiringPiI2CWriteReg8(fd, 0x38, 0x9f);
}
void MainWindow::adxl345_read_xyz(int fd)
{
    char x0, y0, z0, x1, y1, z1;

    x0 = 0xff - wiringPiI2CReadReg8(fd, 0x32);
    x1 = 0xff - wiringPiI2CReadReg8(fd, 0x33);
    y0 = 0xff - wiringPiI2CReadReg8(fd, 0x34);
    y1 = 0xff - wiringPiI2CReadReg8(fd, 0x35);
    z0 = 0xff - wiringPiI2CReadReg8(fd, 0x36);
    z1 = 0xff - wiringPiI2CReadReg8(fd, 0x37);
    int x,y,z;
    x = (int)(x1 << 8) + (int)x0;
    y = (int)(y1 << 8) + (int)y0;
    z = (int)(z1 << 8) + (int)z0;
    ui->lineEdit_x->setText(QString ::number(x,10));
    ui->lineEdit_y->setText(QString ::number(y,10));
    ui->lineEdit_z->setText(QString ::number(z,10));
    qDebug("%d,%d,%d",x,y,z);
}

void MainWindow::on_read_button_clicked()
{
    if(index==0)
    {
        timer->start(200);index=1;
    }
    else
    {
        timer->stop();index=0;
    }
}
