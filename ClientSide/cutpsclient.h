#ifndef CUTPSCLIENT_H
#define CUTPSCLIENT_H

#include <QtCore>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <ui_loginPage.h>

#include "clientconnection.h"
#include "logincontroller.h"
#include "studentcontroller.h"
#include "cmcontroller.h"

namespace Ui {
class MainWindow;
}

class cuTPSClient : public QMainWindow
{
    Q_OBJECT
public:
    explicit cuTPSClient(QWidget *parent = 0);
    ~cuTPSClient();

public slots:
    void getLoginState(QString role, QString userID);
    void getStudentMsg(QString role, QString message);
    void getLogoutState(QString role);
private:
    Ui::MainWindow *ui;
    ClientConnection *c;
    LoginController *logincontrol;
    StudentController *studentControl;
    CmController *cmControl;
    QString userIDString;
};

#endif // CUTPSCLIENT_H
