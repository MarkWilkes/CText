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

    }else if(index.compare("getCourseFromIDRequest") == 0){

        qDebug() << "get course from ID request being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return getCourseFromID(info[0],info[1]);

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

    }else if(index.compare("addCourseRequest")==0){

        qDebug() << "add Course request being processed" << endl;
        QStringList info = data.split("|");
        return addCourse(info[0],info[1].append("|").append(info[2]).append("\r\n"));

    }else if(index.compare("addBookRequest")==0) {

        qDebug() << "add Book request being processed" << endl;
        QStringList info = data.split("|");
        return addBook(info[0],info[2].append("|").append(info[3]).append("|").append(info[4]).append("|").append("\r\n"));

    }else if(index.compare("addChapterRequest")==0) {

        qDebug() << "add Chapter request being processed" << endl;
        QStringList info = data.split("|");
        return addChapter(info[0],info[2].append("|").append(info[3]).append("|").append(info[4]).append("|").append("\r\n"));


    }else if(index.compare("addSectionRequest")==0) {

        qDebug() << "add Section request being processed" << endl;
        QStringList info = data.split("|");
        return addSection(info[0],info[2].append("|").append(info[3]).append("|").append(info[4]).append("\r\n"));


    }else if(index.compare("nextIDRequest")==0) {

        qDebug() << "get nextID request being processed" << endl;
        QStringList info = data.split("|");
        qDebug() <<  info[0] + " " + info[1] << endl;
        return getNextID(info[0],info[1]);

    }else if(index.compare("addXtoYRequest")==0){

        qDebug() << "addXtoY request being processed" << endl;
        QStringList info = data.split("|");
        QString temp = info[1];
        temp.append("|").append(info[2]).append("|").append(info[3]);
        qDebug() <<  info[0] + " " + temp << endl;
        return addSubContent(info[0],temp);
    }else if(index.compare("completeCart") == 0){

        qDebug()<< "completion of cart being processed" << endl;
        QStringList info = data.split("|");
        qDebug() << info[0] + " " + info[1] << endl;
        return completeCart(info[0],info[1]);
    }else if(index.compare("getEMail") == 0){

        qDebug() << "get Email of student user" << endl;
        return getEmail(data);
    }else if(index.compare("editContent") == 0){
        //uri|type|id|newName|newPrice

        qDebug() << "addXtoY request being processed" << endl;
        QStringList info = data.split("|");
        QString temp = info[1];
        temp.append("|").append(info[2]).append("|").append(info[3]).append("|").append(info[4]);
        qDebug() <<  info[0] + " " + temp << endl;

        return editContent(info[0],temp);

    }else if(index.compare("deleteContent")==0){
        //uri|type|id
        qDebug() << "addXtoY request being processed" << endl;
        QStringList info = data.split("|");
        QString temp = info[1];
        temp.append("|").append(info[2]);
        qDebug() <<  info[0] + " " + temp << endl;

        return deleteContent(info[0],temp);

    }else if(index.compare("getAllCourse") == 0){

        qDebug()<< "get all the course request of cart being processed" << endl;
        qDebug() << data << endl;
        return getAllCourse(data);

    }else {
        return ("invalid request");
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

QString cuTPS::getCourseFromID(QString userID, QString courseID)
{
    if(accessControl.isLoggedIn(userID)
            &&accessControl.getUser(userID)->getUserType() == "Student")
    {
        QString result = datacontrol->getCourseFromID(courseID);
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
            (accessControl.getUser(userID)->getUserType() == "Student" ||
             accessControl.getUser(userID)->getUserType() == "ContentManager"))
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
            (accessControl.getUser(userID)->getUserType() == "Student" ||
            accessControl.getUser(userID)->getUserType() == "ContentManager"))
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
            (accessControl.getUser(userID)->getUserType() == "Student") ||
            accessControl.getUser(userID)->getUserType() == "ContentManager")
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
            if(cartList[1].compare(bookID) == 0 || cartList[1].contains(bookID+",")|| cartList[1].contains(","+bookID)){
                return "already exists";
            }
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
            if(cartList[2].compare(chapterID) == 0 || cartList[2].contains(chapterID+",")|| cartList[2].contains(","+chapterID)){
                return "already exists";
            }
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
            if(cartList[3].compare(sectionID) == 0 || cartList[3].contains(sectionID+",")|| cartList[3].contains(","+sectionID)){
                return "already exists";
            }
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

QString cuTPS::completeCart(QString userID, QString cartID){
    datacontrol->addOrder(userID, cartID);
    return setCart(cartID.append("|||"));
}

QString cuTPS::getNextID(QString userID, QString contentType){

    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "ContentManager"){

        QString result = datacontrol->getNewID(contentType);
        return result;

    } else {
        return QString("fail");
    }
}

QString cuTPS::addCourse(QString userID, QString courseInfo){
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "ContentManager"){

        QString result = datacontrol->addCourse(courseInfo);
        return result;

    } else {
        return QString("fail");
    }
}

QString cuTPS::addBook(QString userID, QString bookInfo){
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "ContentManager"){

        QString result = datacontrol->addBook(bookInfo);
        return result;

    } else {
        return QString("fail");
    }
}

QString cuTPS::addChapter(QString userID, QString chapterInfo){
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "ContentManager"){

        QString result = datacontrol->addChapter(chapterInfo);
        return result;

    } else {
        return QString("fail");
    }
}

QString cuTPS::addSection(QString userID, QString sectionInfo){
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "ContentManager"){

        QString result = datacontrol->addSection(sectionInfo);
        return result;

    } else {
        return QString("fail");
    }
}

QString cuTPS::addSubContent(QString userID, QString data){
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "ContentManager"){

        QString result = datacontrol->addSubContent(data);
        return result;

    } else {
        return QString("fail");
    }
}

QString cuTPS::getEmail(QString userID){
    if(accessControl.isLoggedIn(userID) &&
            accessControl.getUser(userID)->getUserType() == "Student"){
        QString result = datacontrol->getEMail(userID);
        return result;
    }
}


QString cuTPS::editContent(QString userID, QString data){
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "ContentManager"){

        QString result = datacontrol->editContent(data);
        return result;

    } else {
        return QString("fail");
    }
}

QString cuTPS::deleteContent(QString userID, QString data){
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "ContentManager"){

        QString result = datacontrol->deleteContent(data);
        return result;

    } else {
        return QString("fail");
    }
}

QString cuTPS::getAllCourse(QString userID)
{
    if(accessControl.isLoggedIn(userID)&&
            accessControl.getUser(userID)->getUserType() == "ContentManager"){

        QString result = datacontrol->getAllCourse();
        return result;

    } else {
        return QString("fail");
    }
}
