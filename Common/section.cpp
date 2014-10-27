#include "section.h"

Section::Section(QString id, QString name, QString price):
    Item(id,name)
{
    this->price = price.toFloat();
}


QString Section::toString()
{
    QString temp = ID.append("|").append(Name).append("|")
            .append(QString::number(price));
    return temp;
}
