#include "item.h"

Item::Item(QString ID, QString name):
    ID(ID),
    Name(name)
{
}
QString Item::getID() const
{
    return ID;
}

void Item::setID(const QString &value)
{
    ID = value;
}
QString Item::getName() const
{
    return Name;
}

void Item::setName(const QString &value)
{
    Name = value;
}


