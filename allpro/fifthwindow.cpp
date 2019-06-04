#include "fifthwindow.h"
#include "ui_fifthwindow.h"

FifthWindow::FifthWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FifthWindow)
{
    wiringPiSetup();
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    pinMode(23,INPUT);
    pinMode(24,INPUT);
    pinMode(25,INPUT);
    index=0;c1=0;c2=0;c3=0;v1=0;v2=0;v3=0;
    count=1;pressing=0;pressed=0;free=1;pressing2=0;pressed2=0;free2=1;
    palette.setColor(QPalette::Background,QColor(225,0,0));
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->setInterval(500);
}

FifthWindow::~FifthWindow()
{
    timer->destroyed();
    delete ui;
}

void FifthWindow::timerUpDate()
{
    init();
    if(free==1&&c1==1){pressing=1;free=0;}
    if(c1==2&&pressing==1){pressed=1;pressing=0;}
    if(pressed==1&&c1==2){pressed=0;free=1;c1=0;count++;if(count>3)count=1;}
    init2();
    switch(count)
    {
        case 1:ui->label_n1->setAutoFillBackground(true);ui->label_n1->setPalette(palette);break;
        case 2:ui->label_n2->setAutoFillBackground(true);ui->label_n2->setPalette(palette);break;
        case 3:ui->label_n3->setAutoFillBackground(true);ui->label_n3->setPalette(palette);break;
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
void FifthWindow::init2()
{
    ui->label_n1->setAutoFillBackground(false);
    ui->label_n2->setAutoFillBackground(false);
    ui->label_n3->setAutoFillBackground(false);
    ui->label_n1->setText(QString::number(v1,10));
    ui->label_n2->setText(QString::number(v2,10));
    ui->label_n3->setText(QString::number(v3,10));
}
void FifthWindow::init()
{
    if(digitalRead(23)==1){ui->label_button_1->setAutoFillBackground(true);ui->label_button_1->setPalette(palette);c1=1;}
    else {ui->label_button_1->setAutoFillBackground(false);c1=2;}
    if(digitalRead(24)==1){ui->label_button_2->setAutoFillBackground(true);ui->label_button_2->setPalette(palette);c2=1;}
    else {ui->label_button_2->setAutoFillBackground(false);c2=2;}
    if(digitalRead(25)==1){ui->label_button_3->setAutoFillBackground(true);ui->label_button_3->setPalette(palette);c3=1;}
    else {ui->label_button_3->setAutoFillBackground(false);c3=2;}
}


void FifthWindow::on_pushButton_view_clicked()
{
    if(index==0)
    timer->start(200);
    else timer->stop();
}

