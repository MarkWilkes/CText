#include "course.h"

Course::Course(QString id, QString name):
    Item(id, name)
{
}

QList<Book *> Course::getBooks() const
{
    return books;
}

void Course::setBooks(const QList<Book *> &value)
{
    books = value;
}

void Course::addBook(Book *value)
{
    books.push_back(value);
}

