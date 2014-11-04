#include "datacontroller.h"

dataController::dataController()
{
}

bool dataController::verifyUser(QString userID, QString &userName, QString &role, QString &courses)
{
    QFile file("../ServerSide/Data/User.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the User data" << endl;
    }
    bool result = false;
    QString temp = QString(file.readLine()); //skip the first useless Line
    while(!file.atEnd())
    {
        temp = QString(file.readLine());
        QStringList infoUserSplit = temp.split("|");
        QString data_userID = infoUserSplit[0];
        if(userID == data_userID)
        {            
            userName = infoUserSplit[1];
            role = infoUserSplit[2];
            role = role.simplified();
            if(role == "Student")
            {
                courses = infoUserSplit[3];
                courses = courses.simplified();
            }
            result = true;
            break;
        }
    }
    file.close();
    return result;
}

QString dataController::getRegistedCourse(QString studentID)
{
    QFile file("../ServerSide/Data/User.txt");
    QFile file2("../ServerSide/Data/Courses.txt");
    if(!file.open(QIODevice::ReadOnly)||!file2.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the data" << endl;
    }
    QString userString = QString(file.readLine());  //skip the first useless line
    QString courseString = QString(file2.readLine());  //skip the first useless line
    QString result;
    while(!file.atEnd())
    {
        userString = QString(file.readLine()).simplified();
        QStringList userInfo = userString.split("|");
        QString userID = userInfo[0];
        if(userID == studentID)
        {
            QString coursesString = userInfo[3];
            QStringList coursesList = coursesString.split(",");
            while(!file2.atEnd())
            {
                courseString = QString(file2.readLine()).simplified();
                for(int i = 0; i < coursesList.size(); i++)
                {
                    if(coursesList.at(i) == courseString.split("|").at(0))
                    {
                        result.append(courseString).append("|");
                    }
                }
            }
        }
    }
    file.close();
    file2.close();
    return result;
}

QString dataController::getBookInfoFromID(QString bookID)
{
    QFile file("../ServerSide/Data/Books.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the Book data" << endl;
    }
    QString temp = QString(file.readLine()); //skip the first useless Line
    while(!file.atEnd())
    {
        temp = QString(file.readLine()).simplified();
        QStringList bookInfo = temp.split("|");
        if(bookID == bookInfo.at(0))
        {
            return temp;
        }
    }
    file.close();
    return QString("");
}

QString dataController::getChapterInfoFromID(QString chapterID)
{
    QFile file("../ServerSide/Data/Chapters.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the Chapter data" << endl;
    }
    QString temp = QString(file.readLine()); //skip the first useless Line
    while(!file.atEnd())
    {
        temp = QString(file.readLine().simplified());
        QStringList chapterInfo = temp.split("|");
        if(chapterID == chapterInfo.at(0))
        {
            return temp;
        }
    }
    file.close();
    return QString("");
}

QString dataController::getSectionInfoFromID(QString sectionID)
{
    QFile file("../ServerSide/Data/Sections.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the Section data" << endl;
    }
    QString temp = QString(file.readLine()); //skip the first useless Line
    while(!file.atEnd())
    {
        temp = QString(file.readLine().simplified());
        QStringList sectionInfo = temp.split("|");
        if(sectionID == sectionInfo.at(0))
        {
            return temp;
        }
    }
    file.close();
    return QString("");
}

QString dataController::getCartInfoFromID(QString CartID)
{
    QFile file("../ServerSide/Data/Cart.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the cart Data" << endl;
    }
    while(!file.atEnd())
    {
        QString temp = QString(file.readLine().simplified());
        QStringList cartInfo = temp.split("|");
        if(CartID == cartInfo.at(0))
        {
            return temp;
        }
    }
    file.close();
    return QString("");
}

QString dataController::getCartID(QString studentID){
    QFile file("../ServerSide/Data/User.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<< "error opening the user Data"<<endl;
    }
    while(!file.atEnd()){
        QString temp = QString(file.readLine().simplified());
        QStringList studentInfo = temp.split("|");
        if(studentID == studentInfo.at(0))
        {
            return studentInfo.at(4);
        }
    }
    file.close();
    return QString("");
}

QString dataController::setCartInfo(QString cart){

    QStringList cartList = cart.split("|");

    QFile file("../ServerSide/Data/Cart.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<< "error opening the Cart Data"<<endl;
        return QString("Fail");
    }
    QTextStream in(&file);
    QStringList line = QStringList();
    while(!in.atEnd()){
        line.append(in.readLine());
    }
    int replaceLine;
    QStringList temp;
    for(int i = 0; i < line.size(); i ++){
        temp = line.at(i).split("|");
        if(temp.at(0).compare(cartList.at(0)) == 0){
            replaceLine = i;
        }
    }
    file.close();

    QFile ofile("../ServerSide/Data/newCart.txt");
    if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
        qDebug()<<"error opening new cart"<<endl;
        return QString("fail");
    }
    QTextStream out(&ofile);
    for(int i = 0; i < line.size(); i++){
        if(i == replaceLine){
            out<<cart +"\r\n";
        }
        else{
            out<<line.at(i) + "\r\n";
        }
    }
    ofile.close();

    file.remove();
    ofile.rename("../ServerSide/Data/newCart.txt","../ServerSide/Data/Cart.txt");
    return QString("success");
}
