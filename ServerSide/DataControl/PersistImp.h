#ifndef PERSISTIMP_H
#define PERSISTIMP_H

class PersistImp {
public:

    virtual ~PersistImp(){}

    //interface for the data controller
    virtual bool verifyUser(QString userID, QString password);

};


#endif // PERSISTIMP_H
