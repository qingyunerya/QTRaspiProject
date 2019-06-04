#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    wiringPiSetup();
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    pinMode(23,OUTPUT);
    pinMode(24,OUTPUT);
    pinMode(25,OUTPUT);
    timer=new QTimer(this);
    serial=new QSerialPort;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(ui->comboBox->currentText()!=info.portName())ui->comboBox->addItem(info.portName());
    }
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    connect(serial,SIGNAL(readyRead()),this,SLOT(Read_Data()));
    timer->setInterval(1000);
    timer->start(200);
}

SecondWindow::~SecondWindow()
{
    timer->destroyed();
    delete ui;
}
void SecondWindow::Read_Data()
{
    QByteArray buf;
    buf=serial->readAll();
    ui->textEdit_accept->setText(QString::fromLocal8Bit(buf));
    qDebug("fdfdf");
}
void SecondWindow::timerUpDate()
{

}


void SecondWindow::on_pushButton_send_clicked()
{
    serial->write(ui->textEdit_send->toPlainText().toLocal8Bit());
}

void SecondWindow::on_pushButton_open_clicked()
{
    serial->close();
    serial->setPortName(ui->comboBox->currentText());
    qDebug(ui->comboBox->currentText().toLocal8Bit());
    if(serial->open(QIODevice::ReadWrite)){qDebug("success");}
    else qDebug("faild");
    serial->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

}
