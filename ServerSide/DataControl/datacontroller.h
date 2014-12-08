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
    QString getCourseFromID(QString courseID);
    QString getBookInfoFromID(QString bookID);
    QString getChapterInfoFromID(QString chapterID);
    QString getSectionInfoFromID(QString sectionID);
    QString getEMail(QString userID);
    QString getAllCourse();

    QString getCartInfoFromID(QString CartID);
    QString getCartID(QString studentID);
    QString setCartInfo(QString cart);
    QString addOrder(QString studentID, QString CartID);

    QString getNewID(QString contentType);

    QString addCourse(QString courseInfo);
    QString addBook(QString bookInfo);
    QString addChapter(QString bookIndex);
    QString addSection(QString bookIndex);
    QString addSubContent(QString data);
    QString editContent(QString content);
    QString deleteContent(QString content);
    QString editCourse(QString content);
    QString deleteCourse(QString content);
    void removeSubContent(QString data);
    void removeCourseFromStudents(QString course);

};

#endif // DATACONTROLLER_H
