#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_sy1_clicked()
{
    FirstWindow *first=new FirstWindow();
    first->show();
}

void MainWindow::on_pushButton_sy2_clicked()
{
    SecondWindow *second=new SecondWindow();
    second->show();
}

void MainWindow::on_pushButton_sy3_clicked()
{
    ThirdWindow *third =new ThirdWindow();
    third->show();
}

void MainWindow::on_pushButton_sy4_clicked()
{
    FourthWindow *fourth=new  FourthWindow();
    fourth->show();
}

void MainWindow::on_pushButton_sy5_clicked()
{
    FifthWindow *fifth=new FifthWindow();
    fifth->show();
}
