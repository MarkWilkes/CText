#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <ui_loginPage.h>
#include "clientconnection.h"

namespace Ui {
class MainWindow;
}

class LoginController : public QObject
{
    Q_OBJECT

public:
    explicit LoginController(QObject *parent = 0, ClientConnection *c = 0, Ui::MainWindow *ui = 0);

private slots:
    void on_Login_button_clicked();

signals:
    void sendLoginState(QString role, QString userID);

private:
    ClientConnection *c;
    Ui::MainWindow *ui;
};

#endif // LOGINCONTROLLER_H
