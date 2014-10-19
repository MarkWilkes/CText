#ifndef CUTPS_H
#define CUTPS_H

#include <QDebug>
#include "accesscontrol.h"

class cuTPS
{
public:
     cuTPS();
    ~cuTPS();

    //API Functions
    QString serveRequest(QString index, QString data);

private:
    AccessControl& accessControl;


};

#endif // CUTPS_H
