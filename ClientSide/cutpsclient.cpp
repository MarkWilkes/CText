#include "cutpsclient.h"

cuTPSClient::cuTPSClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //initialize the client
    c = new ClientConnection();

    //initial the login controller
    logincontrol = new LoginController(this,c,ui);
    connect(logincontrol, SIGNAL(sendLoginState(QString,QString)),
            this,SLOT(getLoginState(QString,QString)));
}

cuTPSClient::~cuTPSClient()
{
    delete ui;
    delete c;
    delete logincontrol;
}

void cuTPSClient::getLoginState(QString role, QString userID)
{
    if(role.compare("Student") == 0){
        QMessageBox::information(this, tr("cuTPS"),tr("Student Login"));
    }else if(role.compare("ContentManager") == 0){
        QMessageBox::information(this, tr("cuTPS"),tr("Content Manager Login"));
    }else if(role.compare("Administrator") == 0){
        QMessageBox::information(this, tr("cuTPS"),tr("Administrator Login"));
    }else if(role.compare("loggedin") == 0){
        //just pop up the message
        QString temp = userID + " : Already logged in";
        QMessageBox::critical(this,tr("cuTPS"),temp);
    }else if(role.compare("fail") == 0){
        //just pop up the message
        QMessageBox::critical(this, tr("cuTPS"), tr("Error User, System don't have this User"));
    }else if(role.compare("empty") == 0){
        //just pop up the message
        QMessageBox::critical(this, tr("cuTPS"), tr("The username is blank! Please enter an username."));
    }
}


