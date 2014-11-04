#include "cart.h"

Cart::Cart(QString id):ID(id),books(0),chapters(0),sections(0)
{
    books = new QList<Book*>();
    chapters = new QList<Chapter*>();
    sections = new QList<Section*>();
}

Cart::~Cart(){
    books->clear();
    chapters->clear();
    sections->clear();
}

void Cart::addBook(Book *book){
    books->push_back(book);
}

void Cart::addChapter(Chapter *chapter){
    chapters->push_back(chapter);
}

void Cart::addSection(Section *section){
    sections->push_back(section);
}

QString Cart::toString(){
    QString temp = ID.append("|");
    for(int i = 0; i < books->size();i++){
        if(i!= 0){
            temp.append(",");
        }
        temp.append((*books)[i]->getID());
    }
    temp.append("|");

    for(int i = 0; i < chapters->size();i++){
        if(i!= 0){
            temp.append(",");
        }
        temp.append((*chapters)[i]->getID());
    }
    temp.append("|");

    for(int i = 0; i < sections->size();i++){
        if(i!= 0){
            temp.append(",");
        }
        temp.append((*sections)[i]->getID());
    }
    return temp;
}
