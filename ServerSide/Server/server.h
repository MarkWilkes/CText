#ifndef SERVER_H
#define SERVER_H
#include "serverconnection.h"
#include "cutps.h"

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent = 0);
    ~Server();

private slots:
    void getRequest();

private:
    ServerConnection *s;
    cuTPS model;

};

#endif
