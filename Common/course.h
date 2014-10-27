#ifndef COURSE_H
#define COURSE_H
#include "item.h"
#include "book.h"
class Course : public Item
{
public:
    Course(QString id, QString name);
    ~Course();

    QString getItemType(){return QString("Course");}

    QList<Book *> getBooks() const;
    void setBooks(const QList<Book *> &value);
    void addBook(Book *value);

private:
    QList<Book*> books;
};

#endif // COURSE_H
