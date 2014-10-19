#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "user.h"

class Administrator : public User
{
    typedef QList<Administrator> AdministratorList;

public:
    Administrator(QString id, QString name);
    QString getUserType(){return QString("Administrator");}
};

#endif // ADMINISTRATOR_H
