#include "book.h"

Book::Book(QString id, QString name, QString price):
    Item(id,name)
{
    this->price = price.toFloat();
}


Book::~Book()
{
    chapters.clear();
}

QString Book::toString()
{
    QString temp = ID.append("|").append(Name).append("|")
            .append(QString::number(price));
    return temp;
}
QList<Chapter *> Book::getChapters() const
{
    return chapters;
}

void Book::setChapters(const QList<Chapter *> &value)
{
    chapters = value;
}

void Book::addChapter(Chapter *value)
{
    chapters.push_back(value);
}

