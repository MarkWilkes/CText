#ifndef CHAPTER_H
#define CHAPTER_H
#include "item.h"
#include "section.h"

class Chapter : public Item
{

public:
    Chapter(QString id, QString name, QString price);
    ~Chapter();
    QString getItemType(){return QString("Chapter");}
    QString toString();

    QList<Section *> getSections() const;
    void setSections(const QList<Section *> &value);
    void addSection(Section *value);

private:
    float price;
    QList<Section*> sections;
};

#endif // CHAPTER_H
