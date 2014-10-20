#include "cutps.h"

cuTPS::cuTPS() :
    accessControl(AccessControl::getInstance())
{

}

cuTPS::~cuTPS()
{

}

QString cuTPS::serveRequest(QString index, QString data)
{
    //First match the request and then do some thing about the data
    if(index.compare("loginRequest") == 0){
        qDebug() << "Login Request being processed" << endl;
        QString result = accessControl.logIn(data);
        if(result.compare("Student") == 0){
            return QString("Student");
        } else if(result.compare("ContentManager") == 0){
            return QString("ContentManager");
        } else if(result.compare("Administrator") == 0){
            return QString("Adminstrator");
        } else if(result.compare("loggedin") == 0){
            return QString("loggedin");
        } else {
            return QString("fail");
        }
    }
}
