#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <firstwindow.h>
#include <secondwindow.h>
#include <thirdwindow.h>
#include <fourthwindow.h>
#include <fifthwindow.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_sy1_clicked();

    void on_pushButton_sy2_clicked();

    void on_pushButton_sy3_clicked();

    void on_pushButton_sy4_clicked();

    void on_pushButton_sy5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
