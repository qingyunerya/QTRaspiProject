#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    ani_timer=new QTimer(this);
    index=0;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    connect(ani_timer,SIGNAL(timeout()),this,SLOT(ani_timer_tick()));
    ani_timer->setInterval(1000);
    timer->setInterval(1000);
    fd=wiringPiI2CSetup(0x53);
    adxl345_init(fd);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow:: paintEvent(QPaintEvent *)
{
    /*QPainter painter(this);
    QPixmap pix;
    pix.load("c:/aa6.jpg");
    painter.translate(100,100);
    painter.rotate(movie_step*3.6);
    painter.translate(0,0);
    painter.drawPixmap(0, 0, 200, 200, pix);*/
    int Ox=19,Oy=129,Ow=781,Oh=361,Zx=Ox+20,Zy=Oy+Oh-20,Lx,Ly,Rx,Ry;
    Lx=Zx-20;Ly=Zy+20;Rx=Zx+Ow-20;Ry=Ly-Oh+20;
    QPainter painter(this);
    painter.setPen(Qt::lightGray);
    painter.drawRect(Ox,Oy,Ow,Oh);
    QPen pen(Qt::black, 3, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawLine(Lx, Zy, Rx, Zy);
    painter.drawLine(Zx, Ry, Zx, Ly);
    if(index==1)
    {

        for(int i=0;i<move;i++)
        {
            /*vx[i]=vx[i]/2;vx[i+1]=vx[i+1]/2;
            vy[i]=vy[i]/2;vy[i+1]=vy[i+1]/2;
            vz[i]=vz[i]/2;vz[i+1]=vz[i+1]/2;*/
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.drawLine(i*5+Zx,Zy-vx[i],i*5+5+Zx,Zy-vx[i+1]);
            pen.setColor(Qt::blue);
            painter.setPen(pen);
            painter.drawLine(i*5+Zx,Zy-vy[i],i*5+5+Zx,Zy-vy[i+1]);
            pen.setColor(Qt::green);
            painter.setPen(pen);
            painter.drawLine(i*5+Zx,Zy-vz[i],i*5+5+Zx,Zy-vz[i+1]);
        }
        /*pen.setColor(Qt::blue);
        painter.setPen(pen);
        for(int i=0;i<move;i++)
        {
            painter.drawLine(i*5+Zx,Zy-vy[i],i*5+5+Zx,Zy-vy[i+1]);
        }
        pen.setColor(Qt::green);
        painter.setPen(pen);
        for(int i=0;i<move;i++)
        {
            painter.drawLine(i*5+Zx,Zy-vz[i],i*5+5+Zx,Zy-vz[i+1]);
        }*/
    }
}
void MainWindow::ani_timer_tick()
{
  this->update();
}
void MainWindow::timerUpDate()
{
    adxl345_read_xyz(fd);
    vx[move]=x;
    vy[move]=y;
    vz[move]=z;
    for(int i=0;i<move;i++)
    {
            vx[i]=vx[i+1];
            vy[i]=vy[i+1];
            vz[i]=vz[i+1];
    }
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
    x = (int)(x1 << 8) + (int)x0;
    y = (int)(y1 << 8) + (int)y0;
    z = (int)(z1 << 8) + (int)z0;
    /*if(x>4095)
    {
        x=(~(x-61440)+1);
    }
    if(y>4095)
    {
        y=(~(y-61440)+1);
    }
    if(z>4095)
    {
        z=(~(z-61440)+1);
    }*/
    ui->lineEdit_x->setText(QString ::number(x,10));
    ui->lineEdit_y->setText(QString ::number(y,10));
    ui->lineEdit_z->setText(QString ::number(z,10));
    double xj,yj,zj,a;
    xj=qAtan(x/qSqrt(y*y+z*z))*180/M_PI;
    yj=qAtan(y/qSqrt(x*x+z*z))*180/M_PI;
    zj=qAtan(z/qSqrt(x*x+y*y))*180/M_PI;
    a=x/qCos((xj/180)*M_PI);
    ui->lineEdit_xj->setText(QString ::number(xj));
    ui->lineEdit_yj->setText(QString ::number(yj));
    ui->lineEdit_zj->setText(QString ::number(zj));
    ui->lineEdit_jsd->setText(QString ::number(a));
    qDebug("%d,%d,%d,%f,%f,%f",x,y,z,xj,yj,zj);
}

void MainWindow::on_read_button_clicked()
{
    if(index==0)
    {
        move=149;
        for(int i=0;i<move+1;i++)
        {
                vx[i]=0;
                vy[i]=0;
                vz[i]=0;
        }
        timer->start(200);ani_timer->start(200);index=1;
    }
    else
    {
        timer->stop();ani_timer->start(200);index=0;
    }
}
