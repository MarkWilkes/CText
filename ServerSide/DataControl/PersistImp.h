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
    virtual QString getRegistedCourse(QString studentID) = 0;
    virtual QString getBookInfoFromID(QString bookID) = 0;
    virtual QString getChapterInfoFromID(QString chapterID) = 0;
    virtual QString getSectionInfoFromID(QString sectionID) = 0;
};


#endif // PERSISTIMP_H
