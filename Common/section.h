#ifndef SECTION_H
#define SECTION_H
#include "item.h"

class Section : public Item
{
public:
    Section(QString id, QString name, QString price);
    QString getItemType(){return QString("Section");}
    QString toString();
private:
    float price;
};

#endif // SECTION_H
