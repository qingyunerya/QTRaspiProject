#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    wiringPiSetup();
    ui->setupUi(this);
    pinMode(27,INPUT);
    pinMode(28,INPUT);
    pinMode(29,INPUT);
    index1=0;c1=0;c2=0;c3=0;v1=0;v2=0;v3=0;
    count=1;pressing=0;pressed=0;free=1;pressing2=0;pressed2=0;free2=1;
    palette.setColor(QPalette::Background,QColor(225,0,0));
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->setInterval(500);
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

void MainWindow::timerUpDate()
{
    init();
    if(free==1&&c1==1){pressing=1;free=0;}
    if(c1==2&&pressing==1){pressed=1;pressing=0;}
    if(pressed==1&&c1==2){pressed=0;free=1;c1=0;count++;if(count>6)count=1;}
    init2();
    switch(count)
    {
        case 1:ui->label_n1->setAutoFillBackground(true);ui->label_n1->setPalette(palette);ui->red_button->clicked();break;
        case 2:ui->label_n2->setAutoFillBackground(true);ui->label_n2->setPalette(palette);ui->green_button->clicked();break;
        case 3:ui->label_n3->setAutoFillBackground(true);ui->label_n3->setPalette(palette);ui->blue_button->clicked();break;
        case 4:ui->label_n4->setAutoFillBackground(true);ui->label_n4->setPalette(palette);ui->all_button->clicked();break;
        case 5:ui->label_n5->setAutoFillBackground(true);ui->label_n5->setPalette(palette);ui->color_changed_button->clicked();break;
        case 6:ui->label_n6->setAutoFillBackground(true);ui->label_n6->setPalette(palette);ui->color_faded_button->clicked();break;

    }
    if(free2==1&&c2==1){pressing2=1;free2=0;}
    if(c2==2&&pressing2==1){pressed2=1;pressing2=0;}
    if(pressed2==1&&c2==2)
    {
        pressed2=0;free2=1;c2=0;
        switch(count)
        {
            case 1:v1++;break;
            case 2:v2++;break;
            case 3:v3++;break;
        }
    }
}
void MainWindow::init2()
{
    ui->label_n1->setAutoFillBackground(false);
    ui->label_n2->setAutoFillBackground(false);
    ui->label_n3->setAutoFillBackground(false);
    ui->label_n4->setAutoFillBackground(false);
    ui->label_n5->setAutoFillBackground(false);
    ui->label_n6->setAutoFillBackground(false);
    ui->label_n1->setText(QString::number(v1,10));
    ui->label_n2->setText(QString::number(v2,10));
    ui->label_n3->setText(QString::number(v3,10));
}
void MainWindow::init()
{
    if(digitalRead(27)==1){ui->label_button_1->setAutoFillBackground(true);ui->label_button_1->setPalette(palette);c1=1;}
    else {ui->label_button_1->setAutoFillBackground(false);c1=2;}
    if(digitalRead(28)==1){ui->label_button_2->setAutoFillBackground(true);ui->label_button_2->setPalette(palette);c2=1;}
    else {ui->label_button_2->setAutoFillBackground(false);c2=2;}
    if(digitalRead(29)==1){ui->label_button_3->setAutoFillBackground(true);ui->label_button_3->setPalette(palette);c3=1;}
    else {ui->label_button_3->setAutoFillBackground(false);c3=2;}
}


void MainWindow::on_pushButton_view_clicked()
{
    if(index1==0)
    timer->start(200);
    else timer->stop();
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
   digitalWrite(23,HIGH);index=1;qDebug("high");
}

void MainWindow::on_green_button_clicked()
{
    init1();
    digitalWrite(24,HIGH);index=2;qDebug("high");
}

void MainWindow::on_blue_button_clicked()
{
    init1();
    digitalWrite(25,HIGH);index=3;qDebug("high");
}

void MainWindow::on_all_button_clicked()
{
    init1();
    digitalWrite(23,HIGH);digitalWrite(24,HIGH);digitalWrite(25,HIGH);qDebug("high");
}

void MainWindow::on_color_faded_button_clicked()
{
    index=5;qDebug("high");
}

void MainWindow::on_color_changed_button_clicked()
{
    index=6;qDebug("high");
}
