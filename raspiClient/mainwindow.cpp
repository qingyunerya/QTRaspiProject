#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QTime>
#include <QTimer>
#include <QNetworkInterface>
#include <QPalette>
#include <QColor>
#include <QColorDialog>
#include <wiringPi.h>
#include <softPwm.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wiringPiSetup();
    pinMode(23,OUTPUT);
    pinMode(24,OUTPUT);
    pinMode(25,OUTPUT);
    pinMode(27,OUTPUT);
    pinMode(28,OUTPUT);
    pinMode(29,OUTPUT);
    digitalWrite(23,HIGH);
    digitalWrite(24,HIGH);
    digitalWrite(25,HIGH);
    digitalWrite(27,HIGH);
    digitalWrite(28,HIGH);
    digitalWrite(29,HIGH);
    this->tcp_client=new QTcpSocket(this);
    connect(this->tcp_client,SIGNAL(connected()),this,SLOT(connected()));
    connect(this->tcp_client,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(this->tcp_client,SIGNAL(readyRead()),this,SLOT(readyread()));
    data_timer=new QTimer(this);
    data_timer->setInterval(100);
    connect(data_timer,SIGNAL(timeout()),this,SLOT(data_timer_tick()));
    data_timer->start();
    //获取所有网络接口的列表
    foreach(QNetworkInterface interface,QNetworkInterface::allInterfaces())
    {
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        foreach(QNetworkAddressEntry entry,entryList)
        {
            if(entry.ip().toString().contains("192.168."))
            {
                ui->lineEdit_ca->setText(entry.ip().toString());
                ui->lineEdit_cp->setText("8080");
                qDebug()<<"ipdrr"<<entry.ip().toString();
            }
        }
    }
    commandList.append("control_key1_click");
    commandList.append("control_key2_click");
    commandList.append("control_key3_click");
    commandList.append("control_led1_click");
    commandList.append("control_led2_click");
    commandList.append("control_led3_click");
    commandList.append("control_readKeys_click");
    commandList.append("control_directControl_click");
    commandList.append("control_recLedOp_click");
    commandList.append("control_recOp_click");
    commandList.append("control_viewLedOp_click");
    commandList.append("control_viewOp_click");
}

MainWindow::~MainWindow()
{
    delete ui;
}
//输出调试
void MainWindow::debug(QString str)
{
    QString time;
    QTime current_time =QTime::currentTime();
    time=current_time.toString("hh:mm:ss:");
    consoleStr=consoleStr+"\n"+time+str;
    ui->textEdit_console->setText(consoleStr);
    ui->textEdit_console->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
}
//输出调试
void MainWindow::debug2(QString str)
{
    QString time;
    QTime current_time =QTime::currentTime();
    time=current_time.toString("hh:mm:ss:");
    consoleStr2=consoleStr2+"\n"+time+str;
    ui->textEdit_console_2->setText(consoleStr2);
    ui->textEdit_console_2->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
    if(isRemoteControl)
    sendCommand(consoleStr2);
}
//操作记录
void MainWindow::opRecord(QString str)
{
    QString time;
    QTime current_time =QTime::currentTime();
    time=current_time.toString("hh:mm:ss:");
    opRecordStr=opRecordStr+"\n"+time+str;
}

//灯动作记录
void MainWindow::opLedRecord(QString str)
{
    QString time;
    QTime current_time =QTime::currentTime();
    time=current_time.toString("hh:mm:ss:");
    opLedRecordStr=opLedRecordStr+"\n"+time+str;
}

//连接服务端
void MainWindow::on_connectToSever_clicked()
{
    QString address=ui->lineEdit_ca->text();
    QString sport=ui->lineEdit_cp->text();
    quint16 port=quint16(sport.toUInt());

    if(!this->tcp_client->isOpen())
    {
        this->tcp_client->connectToHost(address,port,QTcpSocket::ReadWrite);
        ui->connectToSever->setText(QStringLiteral("断开连接"));
        debug(QStringLiteral("连接服务器"));
    }
    else
    {
        tcp_client->close();
        debug(QString::number(this->tcp_client->isOpen())+QStringLiteral("测试"));
        ui->connectToSever->setText(QStringLiteral("连接服务器"));
        debug(QStringLiteral("断开连接"));
    }

}

//连接到服务器
void MainWindow::connected()
{
    debug(QStringLiteral("连接服务器成功"));
    debug2("开始运程控制");
    opRecord("开始运程控制");
    isRemoteControl=true;
}

//发送数据
void MainWindow::on_c_send_clicked()
{
     QString str=ui->textEdit_cs->toPlainText();
     QByteArray ba=str.toUtf8();
     this->tcp_client->write(ba);
}

//开始读取数据
void MainWindow::readyread()
{
     debug(QStringLiteral("接受到服务端数据"));
     QString carr=QString::fromUtf8(this->tcp_client->readAll());
     ui->textEdit_ca->setText(carr);
     if(curCommand.compare(acceptCommand(),Qt::CaseSensitive)!=0){curCommand=acceptCommand();}
     if(isRemoteControl)
     {
         int index;
         foreach (QString command,commandList)
         {
             if(curCommand.contains(command))
             {
                 index=commandList.indexOf(command);
                 debug2(QString::number(index,10));
             }
         }
         switch (index)
         {
             case 0:
             debug2("远程点击了按钮1");
             opRecord("远程点击了按钮1");
             ui->pushButton_key1->click();
             break;
             case 1:
             debug2("远程点击了按钮2");
             opRecord("远程点击了按钮2");
             ui->pushButton_key2->click();
             break;
             case 2:
             debug2("远程点击了按钮3");
             opRecord("远程点击了按钮3");
             ui->pushButton_key3->click();
             break;
             case 3:
             debug2("远程点击了led1");
             opRecord("远程点击了led1");
             ui->pushButton_led1->click();
             break;
             case 4:
             debug2("远程点击了led2");
             opRecord("远程点击了led2");
             ui->pushButton_led2->click();
             break;
             case 5:
             debug2("远程点击了led3");
             opRecord("远程点击了led3");
             ui->pushButton_led3->click();
             break;
             case 6:
             debug2("远程点击了readkeys");
             opRecord("远程点击了readkeys");
             ui->pushButton_readKeys->click();
             break;
             case 7:
             debug2("远程点击了directcontrol");
             opRecord("远程点击了directcontrol");
             ui->pushButton_directControl->click();
             break;
             case 8:
             debug2("远程点击了recledop");
             opRecord("远程点击了recledop");
             ui->pushButton_recLed->click();
             break;
             case 9:
             debug2("远程点击了recoprate");
             opRecord("远程点击了recoprate");
             ui->pushButton_recOperate->click();
             break;
             case 10:
             debug2("远程点击了viewledop");
             opRecord("远程点击了viewledop");
             ui->pushButton_viewLedOp->click();
             break;
             case 11:
             debug2("远程点击了viewop");
             opRecord("远程点击了viewop");
             ui->pushButton_viewOp->click();
             break;
             default:
             break;
         }
      }
}
//断开服务端连接
void MainWindow::disconnected()
{
    debug(QStringLiteral("已断开服务端连接"));
    ui->connectToSever->setText(QStringLiteral("连接服务端"));
    debug2("运程控制中断");
    isRemoteControl=false;
}
//发送命令
void MainWindow::sendCommand(QString str)
{
        QString time;
        QTime current_time =QTime::currentTime();
        time=current_time.toString("hh:mm:ss:");
        time=time+str;
        QByteArray ba=time.toUtf8();
        this->tcp_client->write(ba);
        this->tcp_client->flush();
}
//接收命令
QString MainWindow::acceptCommand()
{
    QString carr=ui->textEdit_ca->toPlainText();
    return carr;
}
void MainWindow::init()
{
    palette.setColor(QPalette::Button,QColor(204,204,204));
    if(digitalRead(23)==0){ui->pushButton_key1->setFlat(true);ui->pushButton_key1->setAutoFillBackground(true);ui->pushButton_key1->setPalette(palette);c1=1;}
    else {ui->pushButton_key1->setAutoFillBackground(false);c1=2;}
    if(digitalRead(24)==0){ui->pushButton_key1->setFlat(true);ui->pushButton_key2->setAutoFillBackground(true);ui->pushButton_key2->setPalette(palette);c2=1;}
    else {ui->pushButton_key2->setAutoFillBackground(false);c2=2;}
    if(digitalRead(25)==0){ui->pushButton_key1->setFlat(true);ui->pushButton_key3->setAutoFillBackground(true);ui->pushButton_key3->setPalette(palette);c3=1;}
    else {ui->pushButton_key3->setAutoFillBackground(false);c3=2;}
    if(free==1&&c1==1){pressing=1;free=0;}
    if(c1==2&&pressing==1){pressed=1;pressing=0;}
    if(pressed==1&&c1==2)
    {
        pressed=0;free=1;c1=0;
        ui->pushButton_key1->click();
        debug2("你点击了树梅派上的key1按钮");
        opRecord("你点击了树梅派上的key1按钮");
    }
    if(free2==1&&c2==1){pressing2=1;free2=0;}
    if(c2==2&&pressing2==1){pressed2=1;pressing2=0;}
    if(pressed2==1&&c2==2)
    {
        pressed2=0;free2=1;c2=0;
        ui->pushButton_key2->click();
        debug2("你点击了树梅派上的key2按钮");
        opRecord("你点击了树梅派上的key2按钮");
    }
    if(free3==1&&c3==1){pressing3=1;free3=0;}
    if(c3==2&&pressing3==1){pressed3=1;pressing3=0;}
    if(pressed3==1&&c3==2)
    {
        pressed3=0;free3=1;c3=0;
        ui->pushButton_key3->click();
        debug2("你点击了树梅派上的key3按钮");
        opRecord("你点击了树梅派上的key3按钮");
    }
}
void MainWindow::data_timer_tick()
{
    init();
    if(isReadKeys)
    {
        QString str;
        str.sprintf("是否点击：按钮1：%s，按钮2：%s，按钮3：%s",c1==1?"是":"否",c2==1?"是":"否",c3==1?"是":"否");
        debug2(str);
    }
}
void MainWindow::on_pushButton_readKeys_clicked()
{ 
    if(!isReadKeys)
    {
        debug2("实时读取按钮状态中：");
        opRecord("实时读取按钮状态中：");
        ui->pushButton_readKeys->setText("停止读取");
        isReadKeys=true;
    }
    else {ui->pushButton_readKeys->setText("读取按钮状态");isReadKeys=false;opRecord("停止读取按钮状态中：");}
    QString str;
    str.sprintf("remote_status_isReadkeys:%s",isReadKeys?"true":"false");
    sendCommand(str);
}

void MainWindow::on_pushButton_key1_clicked()
{
    c1=1;
    if(isControlLed)
    {
        ui->pushButton_led1->click();
    }
    else if(isRemoteControl);
    else {debug2("直接点击了按钮1：");opRecord("直接点击了按钮1：");}
}

void MainWindow::on_pushButton_key2_clicked()
{
    c2=1;
    if(isControlLed)
    {
        ui->pushButton_led2->click();
    }
    else if(isRemoteControl);
    else {debug2("直接点击了按钮2：");opRecord("直接点击了按钮2：");}
}

void MainWindow::on_pushButton_key3_clicked()
{
    c3=1;
    if(isControlLed)
    {
        ui->pushButton_led3->click();
    }
    else if(isRemoteControl);
    else {debug2("直接点击了按钮3：");opRecord("直接点击了按钮3：");}
}

void MainWindow::on_pushButton_directControl_clicked()
{
    if(!isControlLed)
    {
        debug2("直接控制led灯中：");
        opRecord("直接控制led灯中：");
        ui->pushButton_directControl->setText("停止直控");
        isControlLed=true;
    }
    else {ui->pushButton_directControl->setText("直接控制灯：");debug2("停止直接控制led灯中：");opRecord("停止直接控制led灯中：");isControlLed=false;}
    QString str;
    str.sprintf("remote_status_isdirectControl:%s",isControlLed?"true":"false");
    sendCommand(str);
}

void MainWindow::on_pushButton_led1_clicked()
{
    if(!l1)
    {
        digitalWrite(27,LOW);
        debug2("点亮led1");opRecord("点亮led1");opLedRecord("点亮led1");
        palette.setColor(QPalette::Button,QColor(255,255,0));
        ui->pushButton_led1->setFlat(true);
        ui->pushButton_led1->setAutoFillBackground(true);
        ui->pushButton_led1->setPalette(palette);
        l1=true;
    }
    else {digitalWrite(27,HIGH);l1=true;debug2("熄灭led1");opRecord("熄灭led1");opLedRecord("熄灭led1");ui->pushButton_led1->setAutoFillBackground(false);l1=false;}
    QString str;
    str.sprintf("remote_status_l1:%s",l1?"true":"false");
    sendCommand(str);
}

void MainWindow::on_pushButton_led2_clicked()
{
    if(!l2)
    {
        digitalWrite(28,LOW);
        debug2("点亮led2");opRecord("点亮led2");opLedRecord("点亮led2");
        palette.setColor(QPalette::Button,QColor(255,255,0));
        ui->pushButton_led2->setFlat(true);
        ui->pushButton_led2->setAutoFillBackground(true);
        ui->pushButton_led2->setPalette(palette);
        l2=true;
    }
    else {digitalWrite(28,HIGH);debug2("熄灭led2");opRecord("熄灭led2");opLedRecord("熄灭led2");ui->pushButton_led2->setAutoFillBackground(false);l2=false;}
    QString str;
    str.sprintf("remote_status_l2:%s",l2?"true":"false");
    sendCommand(str);
}

void MainWindow::on_pushButton_led3_clicked()
{
    if(!l3)
    {
        digitalWrite(29,LOW);
        debug2("点亮led3");opRecord("点亮led3");opLedRecord("点亮led3");
        palette.setColor(QPalette::Button,QColor(255,255,0));
        ui->pushButton_led3->setFlat(true);
        ui->pushButton_led3->setAutoFillBackground(true);
        ui->pushButton_led3->setPalette(palette);
        l3=true;
    }
    else {digitalWrite(29,HIGH);l3=true;debug2("熄灭led3");opRecord("熄灭led3");opLedRecord("熄灭led3");ui->pushButton_led3->setAutoFillBackground(false);l3=false;}
    QString str;
    str.sprintf("remote_status_l3:%s",l3?"true":"false");
    sendCommand(str);
}

void MainWindow::on_pushButton_recLed_clicked()
{
    debug2("记录灯动作完毕");
    opRecord("记录灯动作完毕");
    isRecLedOp=true;
}

void MainWindow::on_pushButton_recOperate_clicked()
{
    debug2("记录按钮操作完毕");
    opRecord("记录按钮操作完毕");
    isRecOp=true;
}

void MainWindow::on_pushButton_viewLedOp_clicked()
{
    if(isRecLedOp)
    debug2(opLedRecordStr);
    else debug2("尚未记录");
}

void MainWindow::on_pushButton_viewOp_clicked()
{
    if(isRecOp)
    debug2(opRecordStr);
    else debug2("尚未记录");
}
