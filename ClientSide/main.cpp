#include <QApplication>
#include "cutpsclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cuTPSClient client;
    client.show();
    return a.exec();
}
