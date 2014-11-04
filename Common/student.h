#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "course.h"

class Student : public User
{
    typedef QList<Student> StudentList;

public:
    Student(QString id, QString name, QString cartid);
    QString getUserType(){return QString("Student");}

    QList<Course *> getCourses() const;
    void setCourses(const QList<Course *> &value);
    void addCourse(Course *value);

private:
    QList<Course*> courses;
    QString cartID;

};

#endif // STUDENT_H
