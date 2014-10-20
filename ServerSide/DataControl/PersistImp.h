#ifndef PERSISTIMP_H
#define PERSISTIMP_H


#include "../common/student.h"
#include "../common/contentmanager.h"
#include "../common/administrator.h"
#include <QtCore>

class PersistImp {
public:

    virtual ~PersistImp(){}

    //interface for the data controller
    virtual bool verifyUser(QString userID, QString &userName, QString &role) = 0;

};


#endif // PERSISTIMP_H
