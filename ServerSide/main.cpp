#include <QApplication>
#include <QtCore>

#include "Server/server.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Server s;
    return app.exec();
}
