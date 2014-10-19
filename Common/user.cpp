#include "user.h"

User::User(QString id, QString name)
    : ID(id),
      UserName(name)
{
}

QString User::getID() const
{
    return ID;
}

void User::setID(QString value)
{
    ID = value;
}
QString User::getUserName() const
{
    return UserName;
}

void User::setUserName(const QString &value)
{
    UserName = value;
}


