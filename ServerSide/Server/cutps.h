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
private:
    AccessControl& accessControl;
    dataController *datacontrol;
};

#endif // CUTPS_H
