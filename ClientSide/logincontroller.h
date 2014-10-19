#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QMainWindow>
#include <QMessageBox>
#include "clientconnection.h"

namespace Ui {
class MainWindow;
}

class LoginController : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginController(QWidget *parent = 0);
    ~LoginController();

private slots:
    void on_Login_button_clicked();

private:
    Ui::MainWindow *ui;
    ClientConnection *c;
};

#endif // LOGINCONTROLLER_H
