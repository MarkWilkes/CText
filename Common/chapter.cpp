#include "chapter.h"

Chapter::Chapter(QString id, QString name, QString price):
    Item(id,name)
{
    this->price = price.toFloat();
}

Chapter::~Chapter()
{
    sections.clear();
}

QString Chapter::toString()
{
    QString temp = ID.append("|").append(Name).append("|")
            .append(QString::number(price));
    return temp;
}
QList<Section *> Chapter::getSections() const
{
    return sections;
}

void Chapter::setSections(const QList<Section *> &value)
{
    sections = value;
}

void Chapter::addSection(Section *value)
{
    sections.push_back(value);
}

