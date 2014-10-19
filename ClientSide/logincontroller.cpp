#include "logincontroller.h"
#include "ui_loginPage.h"

LoginController::LoginController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Login_button, SIGNAL(clicked()), this, SLOT(on_Login_button_clicked()));
    //initialize the client
    c = new ClientConnection();
    //set the username textfiel as the mian focus
    ui->username->setFocus();
}

LoginController::~LoginController()
{
    delete ui;
    delete c;
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
        if(!(role.compare("false") == 0)){

            //If user exists then put the username on the top right corner label
            userNameString = ui->userName->text();

            //Find out what kind of user logged on, then call the correct initialize function
            if(role.compare("") == 0){
                //to be continue
            } else if (role.compare("loggedin") == 0) {
                QMessageBox::critical(this,tr("TAEval"),tr("Already logged on."));
            }
        } else {
            QMessageBox::critical(this, tr("cuTPS"), tr("The username is blank! Please enter an username."));
        }
    }
}
