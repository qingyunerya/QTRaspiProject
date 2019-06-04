#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    wiringPiSetup();
    ui->setupUi(this);
    pinMode(23,OUTPUT);
    pinMode(24,OUTPUT);
    pinMode(25,OUTPUT);
    index=0;num=0;num2=0;
    timer1=new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(timerUpDate1()));
    timer1->setInterval(1000);
    timer1->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init1()
{
    digitalWrite(23,LOW);
    digitalWrite(24,LOW);
    digitalWrite(25,LOW);
    softPwmStop(23);
    softPwmStop(24);
    softPwmStop(25);
    timer1->setInterval(1000);
}
void MainWindow::init3()
{
    softPwmCreate(23,0,100);
    softPwmCreate(24,0,100);
    softPwmCreate(25,0,100);
    softPwmWrite(23,0);
    softPwmWrite(24,0);
    softPwmWrite(25,0);
    timer1->setInterval(10);

}
void MainWindow::timerUpDate1()
{
    ui->red_button->click();
    if(index==6)
    {
        init1();
        if(num<4)
        {
            switch (num)
            {
                case 0:digitalWrite(23,HIGH);break;
                case 1:digitalWrite(24,HIGH);break;
                case 2:digitalWrite(25,HIGH);break;
                case 3:digitalWrite(23,HIGH);digitalWrite(24,HIGH);digitalWrite(25,HIGH);break;
            }
            num++;
        }
        else {num=0;}
    }
    else if(index==5)
    {
        init3();
        if(num2<100)
        {
            num2+=1;
        }
        else {num2=0;num++;}
        if(num<4)
        {
            switch (num)
            {
                case 0:softPwmWrite(23,num2);break;
                case 1:softPwmWrite(24,num2);break;
                case 2:softPwmWrite(25,num2);break;
                case 3:softPwmWrite(23,num2);softPwmWrite(24,num2);softPwmWrite(25,num2);break;
            }
        }
        else {num=0;}

    }
}

void MainWindow::on_red_button_clicked()
{
    init1();
    if(index!=1){digitalWrite(23,HIGH);index=1;qDebug("high");}
    else {digitalWrite(23,LOW);index=0;}
}

void MainWindow::on_green_button_clicked()
{
    init1();
    if(index!=2){digitalWrite(24,HIGH);index=2;qDebug("high");}
    else {digitalWrite(24,LOW);index=0;}
}

void MainWindow::on_blue_button_clicked()
{
    init1();
    if(index!=3){digitalWrite(25,HIGH);index=3;qDebug("high");}
    else {digitalWrite(25,LOW);index=0;}
}

void MainWindow::on_all_button_clicked()
{
    init1();
    if(index!=4){digitalWrite(23,HIGH);digitalWrite(24,HIGH);digitalWrite(25,HIGH);index=4;qDebug("high");}
    else {digitalWrite(23,LOW);digitalWrite(24,LOW);digitalWrite(25,LOW);index=0;}
}

void MainWindow::on_color_faded_button_clicked()
{
    if(index!=5){index=5;qDebug("high");}
    else {index=0;}
}

void MainWindow::on_color_changed_button_clicked()
{
    if(index!=6){index=6;qDebug("high");}
    else
    {
        index=0;
        init1();
    }
}
