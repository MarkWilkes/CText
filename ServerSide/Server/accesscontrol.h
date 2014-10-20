#ifndef ACCESSCONTROL_H
#define ACCESSCONTROL_H

#include "../Common/user.h"
#include "DataControl/datacontroller.h"

typedef QMap<QString, User*> UserList;

class AccessControl
{

public:
    static AccessControl& getInstance(){
        static AccessControl ac;
        return ac;
    }
    ~AccessControl();

    QString logIn(QString userID);
    bool logOut(QString ID);
    bool isLoggedIn(QString ID);
    User *getUser(QString ID);

private:
    AccessControl();
    dataController datacontrol;
    UserList loggedOnUser;

};

#endif // ACCESSCONTROL_H
