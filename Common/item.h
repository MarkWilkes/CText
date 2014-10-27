#ifndef ITEM_H
#define ITEM_H
#include <QtCore>

class Item
{
public:
    Item(QString ID, QString name);

    virtual QString getItemType() = 0;

    QString getID() const;
    void setID(const QString &value);

    QString getName() const;
    void setName(const QString &value);

protected:
    QString ID;
    QString Name;

};

#endif // ITEM_H
