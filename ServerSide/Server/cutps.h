#ifndef CUTPS_H
#define CUTPS_H

#include <QDebug>
#include "accesscontrol.h"
#include "DataControl/PersistImp.h"

class cuTPS
{
public:
     cuTPS();
    ~cuTPS();

    //API Functions
    QString serveRequest(QString index, QString data);

    QString getRegistedCourses(QString studentID);                      //2014FALL,COMP3004:2015WINTER,COMP3000
    QString getCourseFromID(QString userID, QString courseID);          //COMP3004|Object-Oriented Software Engineer|1,2,3
    QString getBookFromID(QString userID, QString bookID);
    QString getChapterFromID(QString userID, QString chapterID);
    QString getSectionFromID(QString userID, QString sectionID);
    QString getEmail(QString userID);
    QString getNextID(QString userID, QString contentType);

    QString getCartFromID(QString userID, QString cartID);
    QString getCartID(QString studentID);
    QString addBooktoCart(QString userID, QString bookID);
    QString addChaptertoCart(QString userID ,QString chapterID);
    QString addSectiontoCart(QString userID, QString sectionID);
    QString setCart(QString cart);
    QString completeCart(QString userID, QString cartID);

    QString addCourse(QString userID, QString bookInfo);
    QString addBook(QString userID, QString bookInfo);
    QString addChapter(QString userID, QString chapterInfo);
    QString addSection(QString userID, QString sectionInfo);
    QString addSubContent(QString userID, QString data);
    QString editContent(QString userID, QString data);
    QString deleteContent(QString userID, QString data);


private:
    AccessControl& accessControl;
    PersistImp *datacontrol;
};

#endif // CUTPS_H
