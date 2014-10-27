#include "cutps.h"

cuTPS::cuTPS() :
    accessControl(AccessControl::getInstance())
{
    datacontrol = new dataController();
}

cuTPS::~cuTPS()
{

}

QString cuTPS::serveRequest(QString index, QString data)
{
    //First match the request and then do some thing about the data
    if(index.compare("loginRequest") == 0){

        qDebug() << "Login Request being processed" << endl;
        QString result = accessControl.logIn(data);
        if(result.compare("Student") == 0){
            return QString("Student");
        } else if(result.compare("ContentManager") == 0){
            return QString("ContentManager");
        } else if(result.compare("Administrator") == 0){
            return QString("Adminstrator");
        } else if(result.compare("loggedin") == 0){
            return QString("loggedin");
        } else {
            return QString("fail");
        }

    }else if(index.compare("logoutRequest") == 0){

        qDebug() << "Logout Request being processed" << endl;
        qDebug() <<  data << endl;
        return accessControl.logOut(data) ? "true" : "false";

    }else if(index.compare("getRegistedCourseRequest") == 0){

        qDebug() << "get registed courses request being processed" << endl;
        return getRegistedCourses(data);

    }else if(index.compare("getBookInfoRequest") == 0){

        qDebug() << "get Book Information request being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return getBookFromID(info[0],info[1]);

    }else if(index.compare("getChapterInfoRequest") == 0){

        qDebug() << "get Chapter Information request being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return getChapterFromID(info[0],info[1]);

    }else if(index.compare("getSectionInfoRequest") == 0){

        qDebug() << "get Section Information request being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return getSectionFromID(info[0],info[1]);
    }
}

QString cuTPS::getRegistedCourses(QString studentID)
{
    if(accessControl.isLoggedIn(studentID)
            &&accessControl.getUser(studentID)->getUserType() == "Student")
    {
        QString result = datacontrol->getRegistedCourse(studentID);
        if(!result.isEmpty())
        {
            return result;
        } else {
            return QString("empty");
        }
    } else {
        return QString("fail");
    }
}

QString cuTPS::getBookFromID(QString userID, QString bookID)
{
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString result = datacontrol->getBookInfoFromID(bookID);
        if(!result.isEmpty())
        {
            return result;
        } else {
            return QString("empty");
        }
    } else {
        return QString("fail");
    }
}

QString cuTPS::getChapterFromID(QString userID, QString chapterID)
{
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString result = datacontrol->getChapterInfoFromID(chapterID);
        if(!result.isEmpty())
        {
            return result;
        } else {
            return QString("empty");
        }
    } else {
        return QString("fail");
    }
}

QString cuTPS::getSectionFromID(QString userID, QString sectionID)
{
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString result = datacontrol->getSectionInfoFromID(sectionID);
        if(!result.isEmpty())
        {
            return result;
        } else {
            return QString("empty");
        }
    } else {
        return QString("fail");
    }
}

