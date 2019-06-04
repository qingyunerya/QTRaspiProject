#include "firstwindow.h"
#include "ui_firstwindow.h"

FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstWindow)
{
    wiringPiSetup();
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    pinMode(23,OUTPUT);
    pinMode(24,OUTPUT);
    pinMode(25,OUTPUT);
    index=0;num=0;num2=0;
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->setInterval(1000);
    timer->start(200);
}

FirstWindow::~FirstWindow()
{
    timer->destroyed();
    qDebug("xiaohui");
    delete ui;
}
void FirstWindow::init()
{
    digitalWrite(23,LOW);
    digitalWrite(24,LOW);
    digitalWrite(25,LOW);
    softPwmStop(23);
    softPwmStop(24);
    softPwmStop(25);
    timer->setInterval(1000);
}
void FirstWindow::init2()
{
    softPwmCreate(23,0,100);
    softPwmCreate(24,0,100);
    softPwmCreate(25,0,100);
    softPwmWrite(23,0);
    softPwmWrite(24,0);
    softPwmWrite(25,0);
    timer->setInterval(10);

}
void FirstWindow::timerUpDate()
{
    if(index==6)
    {
        init();
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
        init2();
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

void FirstWindow::on_red_button_clicked()
{
    init();
    if(index!=1){digitalWrite(23,HIGH);index=1;qDebug("high");}
    else {digitalWrite(23,LOW);index=0;}
}

void FirstWindow::on_green_button_clicked()
{
    init();
    if(index!=2){digitalWrite(24,HIGH);index=2;qDebug("high");}
    else {digitalWrite(24,LOW);index=0;}
}

void FirstWindow::on_blue_button_clicked()
{
    init();
    if(index!=3){digitalWrite(25,HIGH);index=3;qDebug("high");}
    else {digitalWrite(25,LOW);index=0;}
}

void FirstWindow::on_all_button_clicked()
{
    init();
    if(index!=4){digitalWrite(23,HIGH);digitalWrite(24,HIGH);digitalWrite(25,HIGH);index=4;qDebug("high");}
    else {digitalWrite(23,LOW);digitalWrite(24,LOW);digitalWrite(25,LOW);index=0;}
}

void FirstWindow::on_color_faded_button_clicked()
{
    if(index!=5){index=5;qDebug("high");}
    else {index=0;}
}

void FirstWindow::on_color_changed_button_clicked()
{
    if(index!=6){index=6;qDebug("high");}
    else
    {
        index=0;
        init();
    }
}
