#ifndef CART_H
#define CART_H
#include "book.h"
#include "chapter.h"
#include "section.h"

class Cart {
public:
    Cart(QString id);
    ~Cart();

    QString toString();

    void addBook(Book* book);
    void addChapter(Chapter* chapter);
    void addSection(Section* section);

private:
    QString ID;
    QList<Book*>* books;
    QList<Chapter*>* chapters;
    QList<Section*>* sections;
};

#endif // CART_H
