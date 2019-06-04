#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTcpSocket;
class QTimer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void debug(QString str);
    void debug2(QString str);
    void opRecord(QString str);
    void opLedRecord(QString str);
    void sendCommand(QString str);
    QString acceptCommand();
    QList<QString> commandList;
    QString curCommand;
    QTcpSocket *tcp_client;
    QString consoleStr;
    QString consoleStr2;
    QString opRecordStr;
    QString opLedRecordStr;
    QTimer *data_timer;
    QTimer *ani_timer;
    bool isReadKeys=false;
    bool isControlLed=false;
    bool isRecLedOp=false;
    bool isRecOp=false;
    bool isRemoteControl=false;
    int pressing=0;int pressed=0;int free=1;
    int pressing2=0;int pressed2=0;int free2=1;
    int pressing3=0;int pressed3=0;int free3=1;
    int c1=0,c2=0,c3=0;
    bool l1=false,l2=false,l3=false;
    QPalette palette;
    void init();

private slots:

    void readyread();
    void connected();
    void disconnected();
    void on_connectToSever_clicked();
    void on_c_send_clicked();
    void data_timer_tick();
    void on_pushButton_readKeys_clicked();
    
    void on_pushButton_key1_clicked();
    
    void on_pushButton_key2_clicked();
    
    void on_pushButton_key3_clicked();
    
    void on_pushButton_directControl_clicked();
    
    void on_pushButton_led1_clicked();
    
    void on_pushButton_led2_clicked();
    
    void on_pushButton_led3_clicked();
    
    void on_pushButton_recLed_clicked();
    
    void on_pushButton_recOperate_clicked();
    
    void on_pushButton_viewLedOp_clicked();

    void on_pushButton_viewOp_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
