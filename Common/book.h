#ifndef BOOK_H
#define BOOK_H
#include "item.h"
#include "chapter.h"

class Book : public Item
{

public:
    Book(QString id, QString name, QString price);
    //remove all the chapters in this book
    ~Book();
    QString getItemType(){return QString("Book");}
    //toString function only return the ID,Name,price,chapterList of the book
    QString toString();

    QList<Chapter *> getChapters() const;
    void setChapters(const QList<Chapter *> &value);
    void addChapter(Chapter *value);

private:
    float price;
    QList<Chapter*> chapters;
};

#endif // BOOK_H
