#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"

class Student : public User
{
    typedef QList<Student> StudentList;

public:
    Student(QString id, QString name);
    QString getUserType(){return QString("Student");}

private:


};

#endif // STUDENT_H
