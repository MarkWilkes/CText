#include "student.h"

Student::Student(QString id, QString name, QString cartid) :
    User(id,name),cartID(cartid)
{
}

QList<Course *> Student::getCourses() const
{
    return courses;
}

void Student::setCourses(const QList<Course *> &value)
{
    courses = value;
}

void Student::addCourse(Course *value)
{
    courses.push_back(value);
}

