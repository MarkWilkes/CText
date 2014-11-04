#include "cutps.h"

cuTPS::cuTPS() :
    accessControl(AccessControl::getInstance())
{
    datacontrol = new dataController();
}

cuTPS::~cuTPS()
{

}

QString cuTPS::serveRequest(QString index, QString data)
{
    //First match the request and then do some thing about the data
    if(index.compare("loginRequest") == 0){

        qDebug() << "Login Request being processed" << endl;
        QString result = accessControl.logIn(data);
        if(result.compare("Student") == 0){
            return QString("Student");
        } else if(result.compare("ContentManager") == 0){
            return QString("ContentManager");
        } else if(result.compare("Administrator") == 0){
            return QString("Adminstrator");
        } else if(result.compare("loggedin") == 0){
            return QString("loggedin");
        } else {
            return QString("fail");
        }

    }else if(index.compare("logoutRequest") == 0){

        qDebug() << "Logout Request being processed" << endl;
        qDebug() <<  data << endl;
        return accessControl.logOut(data) ? "true" : "false";

    }else if(index.compare("getRegistedCourseRequest") == 0){

        qDebug() << "get registed courses request being processed" << endl;
        return getRegistedCourses(data);

    }else if(index.compare("getBookInfoRequest") == 0){

        qDebug() << "get Book Information request being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return getBookFromID(info[0],info[1]);

    }else if(index.compare("getChapterInfoRequest") == 0){

        qDebug() << "get Chapter Information request being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return getChapterFromID(info[0],info[1]);

    }else if(index.compare("getSectionInfoRequest") == 0){

        qDebug() << "get Section Information request being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return getSectionFromID(info[0],info[1]);
    }else if(index.compare("getCartInfoRequest") == 0){

        qDebug() << "get Cart Information request being processed" << endl;
        QStringList info = data.split("|");
        qDebug() << info[0] + " " +info[1] << endl;
        return getCartFromID(info[0], info[1]);
    }else if(index.compare("getCartID") == 0){

        qDebug() << "get Cart ID request being processed" << endl;
        return getCartID(data);
    }else if(index.compare("addBooktoCart") == 0){
        qDebug()<<"addBooktoCart request is being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return addBooktoCart(info[0],info[1]);
    }else if(index.compare("addChaptertoCart") == 0){
        qDebug()<<"addChaptertoCart request is being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return addChaptertoCart(info[0],info[1]);
    }else if(index.compare("addSectiontoCart") == 0){
        qDebug()<<"addSectiontoCart request is being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return addSectiontoCart(info[0],info[1]);
    }else if(index.compare("setCart") == 0){
        qDebug() << "setCart request is being processed" << endl;
        qDebug() << data << endl;
        return setCart(data);
    }
}

QString cuTPS::getRegistedCourses(QString studentID)
{
    if(accessControl.isLoggedIn(studentID)
            &&accessControl.getUser(studentID)->getUserType() == "Student")
    {
        QString result = datacontrol->getRegistedCourse(studentID);
        if(!result.isEmpty())
        {
            return result;
        } else {
            return QString("empty");
        }
    } else {
        return QString("fail");
    }
}

QString cuTPS::getBookFromID(QString userID, QString bookID)
{
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString result = datacontrol->getBookInfoFromID(bookID);
        if(!result.isEmpty())
        {
            return result;
        } else {
            return QString("empty");
        }
    } else {
        return QString("fail");
    }
}

QString cuTPS::getChapterFromID(QString userID, QString chapterID)
{
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString result = datacontrol->getChapterInfoFromID(chapterID);
        if(!result.isEmpty())
        {
            return result;
        } else {
            return QString("empty");
        }
    } else {
        return QString("fail");
    }
}

QString cuTPS::getSectionFromID(QString userID, QString sectionID)
{
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString result = datacontrol->getSectionInfoFromID(sectionID);
        if(!result.isEmpty())
        {
            return result;
        } else {
            return QString("empty");
        }
    } else {
        return QString("fail");
    }
}

QString cuTPS::getCartFromID(QString userID,QString cartID)
{
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType()=="Student")
    {
        QString result = datacontrol->getCartInfoFromID(cartID);
        if(!result.isEmpty())
        {
            return result;
        }
        else
        {
            return QString("empty");
        }
    }
    else
    {
        return QString("fail");
    }
}

QString cuTPS::getCartID(QString studentID){

    if(accessControl.isLoggedIn(studentID)
            &&accessControl.getUser(studentID)->getUserType() == "Student")
    {
        QString result = datacontrol->getCartID(studentID);
        if(!result.isEmpty())
        {
            return result;
        } else {
            return QString("empty");
        }
    } else {
        return QString("fail");
    }
}

QString cuTPS::addBooktoCart(QString userID, QString bookID){
    if(accessControl.isLoggedIn(userID)
            &&accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString cart = getCartFromID(userID,getCartID(userID));
        QStringList cartList = cart.split("|");
        if(cartList[1].isEmpty()){
            cartList[1] = bookID;
        }
        else{
            cartList[1].append(",").append(bookID);
        }
        cart = cartList[0];
        for(int i = 1; i < cartList.size(); i++){
            cart.append("|").append(cartList[i]);
        }
        return setCart(cart);
    }
    return QString("fail");
}

QString cuTPS::addChaptertoCart(QString userID, QString chapterID){
    if(accessControl.isLoggedIn(userID)
            &&accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString cart = getCartFromID(userID,getCartID(userID));
        QStringList cartList = cart.split("|");
        if(cartList[2].isEmpty()){
            cartList[2] = chapterID;
        }
        else{
            cartList[2].append(",").append(chapterID);
        }
        cart = cartList[0];
        for(int i = 1; i < cartList.size(); i++){
            cart.append("|").append(cartList[i]);
        }
        return setCart(cart);
    }
    return QString("fail");
}

QString cuTPS::addSectiontoCart(QString userID, QString sectionID){
    if(accessControl.isLoggedIn(userID)
            &&accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString cart = getCartFromID(userID,getCartID(userID));
        QStringList cartList = cart.split("|");
        if(cartList[3].isEmpty()){
            cartList[3] = sectionID;
        }
        else{
            cartList[3].append(",").append(sectionID);
        }
        cart = cartList[0];
        for(int i = 1; i < cartList.size(); i++){
            cart.append("|").append(cartList[i]);
        }
        return setCart(cart);
    }
    return QString("fail");
}

QString cuTPS::setCart(QString cart){
    qDebug() << cart << endl;
    return datacontrol->setCartInfo(cart);
}
