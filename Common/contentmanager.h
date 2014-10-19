#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "user.h"

class ContentManager : public User
{
    typedef QList<ContentManager> ContentManagerList;

public:
    ContentManager(QString userID, QString userName);
    QString getUserType(){return QString("ContentManager");}
};

#endif // CONTENTMANAGER_H
