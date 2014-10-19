#ifndef USER_H
#define USER_H
#include <QtCore>

class User
{
public:
    User(QString ID, QString name);

    virtual QString getUserType() = 0;

    QString getID() const;
    void setID(QString value);

    QString getUserName() const;
    void setUserName(const QString &value);

private:
    QString ID;
    QString UserName;
};

#endif // USER_H
