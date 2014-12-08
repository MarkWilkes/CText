#ifndef PERSISTIMP_H
#define PERSISTIMP_H


#include "../Common/student.h"
#include "../Common/contentmanager.h"
#include "../Common/administrator.h"
#include <QtCore>

class PersistImp {
public:

    virtual ~PersistImp(){}

    //interface for the data controller
    virtual bool verifyUser(QString userID, QString &userName, QString &role, QString &courses) = 0;
    virtual QString getCourseFromID(QString courseID) = 0;
    virtual QString getRegistedCourse(QString studentID) = 0;
    virtual QString getBookInfoFromID(QString bookID) = 0;
    virtual QString getChapterInfoFromID(QString chapterID) = 0;
    virtual QString getSectionInfoFromID(QString sectionID) = 0;
    virtual QString getEMail(QString userID) = 0;

    virtual QString getCartInfoFromID(QString CartID) = 0;
    virtual QString getCartID(QString studentID) = 0;
    virtual QString setCartInfo(QString cart) = 0;
    virtual QString addOrder(QString studentID, QString CartID) = 0;

    virtual QString getNewID(QString contentType) = 0;
    virtual QString addCourse(QString courseInfo) = 0;
    virtual QString addBook(QString bookInfo) = 0;
    virtual QString addChapter(QString bookIndex) = 0;
    virtual QString addSection(QString bookIndex) = 0;
    virtual QString addSubContent(QString data) = 0;
    virtual QString editContent(QString content) = 0;
    virtual QString deleteContent(QString content) = 0;
    virtual QString getAllCourse() = 0;
    virtual QString editCourse(QString content)=0;
    virtual QString deleteCourse(QString content)=0;
    virtual void removeSubContent(QString data)=0;
};


#endif // PERSISTIMP_H
