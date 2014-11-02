#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "clientconnection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void clearTest();
    ~MainWindow();

private slots:
    /*Test case 1*/
    void on_pushButton_clicked();

    /*Test case 2*/
    void on_pushButton_2_clicked();

    /*Test case 3*/
    void on_pushButton_3_clicked();

    /*Test case 4*/
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    ClientConnection *c;
};

#endif // MAINWINDOW_H
