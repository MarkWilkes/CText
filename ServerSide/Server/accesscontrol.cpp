#include "accesscontrol.h"

AccessControl::AccessControl()
{
}

AccessControl::~AccessControl()
{
    QList<User*> temp = loggedOnUser.values();
    for(int i = 0; i < temp.size(); i++)
    {
        delete temp[i];
    }
}

QString AccessControl::logIn(QString userID)
{
    if(isLoggedIn(userID)) return "loggedin";
    QString role, userName;
    datacontrol.verifyUser(userID, userName, role);
    if(role == QString("Student"))
    {

    } else if(role == QString("ContentManager")){

    } else if(role == QString("Administrator")){

    }
    return role;

}

bool AccessControl::logOut(QString ID)
{
    if(loggedOnUser.contains(ID))
    {
        delete loggedOnUser.value(ID);
        loggedOnUser.remove(ID);
        return true;
    } else {
        qDebug() << "can't find the user, already log out" << endl;
        return false;
    }
}

bool AccessControl::isLoggedIn(QString ID)
{
    return loggedOnUser.contains(ID);
}

User *AccessControl::getUser(QString ID)
{
    return loggedOnUser.value(ID);
}
