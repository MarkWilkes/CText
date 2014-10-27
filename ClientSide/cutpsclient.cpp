#include "cutpsclient.h"

cuTPSClient::cuTPSClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //initialize the client
    c = new ClientConnection();

    //initial the login controller
    logincontrol = new LoginController(this, c, ui);
    connect(logincontrol, SIGNAL(sendLoginState(QString,QString)),
            this,SLOT(getLoginState(QString,QString)));
    connect(logincontrol, SIGNAL(sendLogoutState(QString)),
            this, SLOT(getLogoutState(QString)));
    //initial the student controller
    studentControl = new StudentController(this, c, ui);
    connect(studentControl, SIGNAL(sendMsg(QString,QString)),
            this,SLOT(getStudentMsg(QString,QString)));

}

cuTPSClient::~cuTPSClient()
{
    delete ui;
    delete c;
    delete logincontrol;
    delete studentControl;
}

void cuTPSClient::getLoginState(QString role, QString userID)
{
    if(role.compare("Student") == 0){
        QMessageBox::information(this, tr("cuTPS"),tr("Student Login"));
        studentControl->initialize(userID);
    }else if(role.compare("ContentManager") == 0){
        QMessageBox::information(this, tr("cuTPS"),tr("Content Manager Login"));
    }else if(role.compare("Administrator") == 0){
        QMessageBox::information(this, tr("cuTPS"),tr("Administrator Login"));
    }else if(role.compare("loggedin") == 0){
        //just pop up the message
        QString temp = userID + " : Already logged in";
        QMessageBox::critical(this,tr("cuTPS"),temp);
        studentControl->initialize(userID);
    }else if(role.compare("fail") == 0){
        //just pop up the message
        QMessageBox::critical(this, tr("cuTPS"), tr("Error User, System don't have this User"));
    }else if(role.compare("empty") == 0){
        //just pop up the message
        QMessageBox::critical(this, tr("cuTPS"), tr("The username is blank! Please enter an username."));
    }
}

void cuTPSClient::getStudentMsg(QString role, QString message)
{
    if(role.compare("critical") == 0){
        QMessageBox::critical(this,tr("cuTPS"),message);
    }else if(role.compare("information") == 0){
        QMessageBox::information(this,tr("cuTPS"),message);
    }
}

void cuTPSClient::getLogoutState(QString role)
{
    if(role == "true"){
        ui->stackedWidget->setCurrentIndex(0);
        QMessageBox::information(this, tr("cuTPS"),tr("Logout successfully"));
    } else {
        ui->stackedWidget->setCurrentIndex(0);
        QMessageBox::information(this, tr("cuTPS"),tr("Already Logout"));
    }
}


