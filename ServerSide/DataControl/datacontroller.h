#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <QtCore>
#include <QDebug>
#include <QFile>

#include "PersistImp.h"

class dataController: public PersistImp
{
public:
    dataController();

    //API
    bool verifyUser(QString userID, QString &userName, QString &role, QString &courses);
    QString getRegistedCourse(QString studentID);
    QString getBookInfoFromID(QString bookID);
    QString getChapterInfoFromID(QString chapterID);
    QString getSectionInfoFromID(QString sectionID);
    QString getCartInfoFromID(QString CartID);
    QString getCartID(QString studentID);
    QString setCartInfo(QString cart);

};

#endif // DATACONTROLLER_H
