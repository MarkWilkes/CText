#ifndef SERVER_H
#define SERVER_H
#include "serverconnection.h"
#include "cutps.h"

class Server
{
public:
    Server();
    ~Server();

private slots:
    void getRequest();

private:
    ServerConnection *s;
    cuTPS model;

};

#endif
