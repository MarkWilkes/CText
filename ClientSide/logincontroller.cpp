#include "logincontroller.h"

LoginController::LoginController(QObject *parent, ClientConnection *cClient, Ui::MainWindow *uiMainWindow) :
    QObject(parent)
{
    ui = uiMainWindow;
    c = cClient;

    connect(ui->Login_button, SIGNAL(clicked()), this, SLOT(on_Login_button_clicked()));
    connect(ui->logout_button, SIGNAL(clicked()), this, SLOT(logOutButtonClicked()));
    connect(ui->logout_button_2, SIGNAL(clicked()), this, SLOT(logOutButtonClicked()));
    //set the username textfiel as the main focus
    ui->username->setFocus();
}

void LoginController::on_Login_button_clicked()
{
    //user name textfield can't be empty
    if(!ui->username->text().isEmpty())
    {
        //Send a login request with the entered username
        QString temp = ui->username->text();
        QString role = c->sendRequest("loginRequest|", temp);

        //Check if the login request was successful otherwise send an error message saying user doesn't exist.
        if(!(role.compare("fail") == 0)){

            //If user exists then put the username on the top right corner label
            QString userID = ui->username->text();
            this->userID = userID;
            //Find out what kind of user logged on, then call the correct initialize function
            if(role.compare("Student") == 0){
                emit sendLoginState("Student", userID);
            }else if(role.compare("ContentManager") == 0){
                emit sendLoginState("ContentManager", userID);
            }else if(role.compare("Administrator") == 0){
                emit sendLoginState("Administrator", userID);
            }else if (role.compare("loggedin") == 0) {
                emit sendLoginState("loggedin", userID);
            }
        } else {
            emit sendLoginState("fail", "");
        }
    } else {
        emit sendLoginState("empty", "");
    }
}

void LoginController::logOutButtonClicked()
{
    QString role = c->sendRequest("logoutRequest|", userID);
    if(role == "true")
    {
        emit sendLogoutState("true");
    } else {
        emit sendLogoutState("false");
    }
}

