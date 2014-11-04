#ifndef CUTPS_H
#define CUTPS_H

#include <QDebug>
#include "accesscontrol.h"
#include "DataControl/datacontroller.h"

class cuTPS
{
public:
     cuTPS();
    ~cuTPS();

    //API Functions
    QString serveRequest(QString index, QString data);

    QString getRegistedCourses(QString studentID);
    QString getBookFromID(QString userID, QString bookID);
    QString getChapterFromID(QString userID, QString chapterID);
    QString getSectionFromID(QString userID, QString sectionID);

    QString getCartFromID(QString userID, QString cartID);
    QString getCartID(QString studentID);
    QString addBooktoCart(QString userID, QString bookID);
    QString addChaptertoCart(QString userID ,QString chapterID);
    QString addSectiontoCart(QString userID, QString sectionID);
    QString setCart(QString cart);

    QString getNextID(QString userID, QString contentType);
    QString addBook(QString userID, QString bookInfo);
    QString addChapter(QString userID, QString chapterInfo);
    QString addSection(QString userID, QString sectionInfo);

private:
    AccessControl& accessControl;
    dataController *datacontrol;
};

#endif // CUTPS_H
