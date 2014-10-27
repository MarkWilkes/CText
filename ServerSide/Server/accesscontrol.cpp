#include "accesscontrol.h"

AccessControl::AccessControl()
{
    datacontrol = new dataController();
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
    QString role, userName, coursesString;

    if(datacontrol->verifyUser(userID, userName, role, coursesString)){
        if(role == QString("Student"))
        {
            Student *temp = new Student(userID, userName);
            loggedOnUser.insert(userID, temp);
        } else if(role == QString("ContentManager")){
            ContentManager *temp = new ContentManager(userID, userName);
            loggedOnUser.insert(userID, temp);
        } else if(role == QString("Administrator")){
            Administrator *temp = new Administrator(userID, userName);
            loggedOnUser.insert(userID, temp);
        }
        return role;
    } else {
        return "fail";
    }

}

bool AccessControl::logOut(QString ID)
{
    if(loggedOnUser.contains(ID))
    {
        delete loggedOnUser.value(ID);
        loggedOnUser.remove(ID);
        return true;
    } else {
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
