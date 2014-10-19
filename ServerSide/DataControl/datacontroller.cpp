#include "datacontroller.h"

dataController::dataController()
{
}

bool dataController::verifyUser(QString userID, QString &userName, QString &role)
{
    QFile file("../ServerSide/Data/User.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the User data" << endl;
    }
    bool result = false;
    QString temp = QString(file.readLine()); //skip the first useless Line
    while(!file.atEnd())
    {
        temp = QString(file.readLine());
        QStringList infoUserSplit = temp.split("|");
        QString data_userID = infoUserSplit[0];
        if(userID == data_userID)
        {
            result = true;
            break;
        }
        userName = infoUserSplit[1];
        role = infoUserSplit[2];
    }
    file.close();
    return result;
}
