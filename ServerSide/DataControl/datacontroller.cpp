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
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the data" << endl;
    }
    QString userString = QString(file.readLine());  //skip the first useless line
    while(!file.atEnd())
    {
        userString = QString(file.readLine()).simplified();
        QStringList userInfo = userString.split("|");
        QString userID = userInfo[0];
        if(userID == studentID)
        {
            QString coursesString = userInfo[3];
            return coursesString;
        }
    }
    file.close();
    return "";
}

QString dataController::getCourseFromID(QString courseID)
{
    QFile file("../ServerSide/Data/Courses.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the data" << endl;
    }
    QString courseString = QString(file.readLine());  //skip the first useless line
    while(!file.atEnd())
    {
        courseString = QString(file.readLine()).simplified();
        if(courseString.split("|").at(0) == courseID)
        {
            return courseString;
        }
    }
    file.close();
    return "";

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

QString dataController::getEMail(QString userID){
    QFile file("../ServerSide/Data/User.txt");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "error opening the User data" <<endl;
    }
    QString temp = QString(file.readLine());
    while(!file.atEnd()){
        temp = QString(file.readLine().simplified());
        QStringList userInfo = temp.split("|");
        if(userID == userInfo.at(0)){
            return userInfo.at(5);
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

QString dataController::addOrder(QString studentID, QString CartID){
    QString cartInfo = getCartInfoFromID(CartID);
    QStringList list = cartInfo.split("|");
    QString cartBooks = list[1];
    QString cartChapters = list[2];
    QString cartSections = list[3];
    QString totalCost = "0.00";

    if(!cartBooks.isEmpty()){
        list = cartBooks.split(",");
        for(int i = 0; i < list.size(); i++){
            QString info = getBookInfoFromID(list[i]);
            QStringList iList = info.split("|");
            totalCost = QString::number(totalCost.toFloat() + iList[2].toFloat());
        }
    }

    if(!cartChapters.isEmpty()){
        list = cartChapters.split(",");
        for(int i = 0; i < list.size(); i++){
            QString info = getChapterInfoFromID(list[i]);
            QStringList iList = info.split("|");
            totalCost = QString::number(totalCost.toFloat() + iList[2].toFloat());
        }
    }

    if(!cartSections.isEmpty()){
        list = cartSections.split(",");
        for(int i = 0; i < list.size(); i++){
            QString info = getSectionInfoFromID(list[i]);
            QStringList iList = info.split("|");
            totalCost = QString::number(totalCost.toFloat() + iList[2].toFloat());
        }
    }
    QString stu = studentID;
    QString order = stu.append("|").append(cartBooks).append("|").append(cartChapters).append("|").append(cartSections);

    order.append("|").append(totalCost).append("|").append(getEMail(studentID)).append("\n");

    QFile file("../ServerSide/Data/Order.txt");
    if(!file.open(QIODevice::Append))
    {
        qDebug() << "error opening the Order data" << endl;
    }

    QTextStream outstream(&file);
    outstream<<order;

    file.close();
    return("yay");
}

QString dataController::getNewID(QString contentType){

    QString reply, temp;

    if(contentType.compare("Book")==0){

        QFile file("../ServerSide/Data/Books.txt");
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "error opening the Book data" << endl;
        }
        while (!file.atEnd()){
            temp = QString(file.readLine());
            if(temp != "")
            {
                reply = temp.split("|").at(0);
            }
        }
        file.close();
        int num = reply.toInt();
        num++;
        reply = QString::number(num);
        return(reply);

    }else if(contentType.compare("Chapter")==0){
        QFile file("../ServerSide/Data/Chapters.txt");
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "error opening the Chapter data" << endl;
        }
        while (!file.atEnd()){
            temp = QString(file.readLine());
            if(temp != "")
            {
                reply = temp.split("|").at(0);
            }
        }
        file.close();
        int num = reply.toInt();
        num++;
        reply = QString::number(num);
        return(reply);

    }else if(contentType.compare("Section")==0){
        QFile file("../ServerSide/Data/Sections.txt");
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "error opening the Section data" << endl;
        }
        while (!file.atEnd()){
            temp = QString(file.readLine());
            if(temp != "")
            {
                reply = temp.split("|").at(0);
            }
        }
        file.close();
        int num = reply.toInt();
        num++;
        reply = QString::number(num);
        return(reply);

    }else{        
        qDebug() << "bad data type" << endl;
        return("fail");
    }
}

QString dataController::addCourse(QString courseInfo) {
    QFile file("../ServerSide/Data/Courses.txt");
    if(!file.open(QIODevice::Append))
    {
        qDebug() << "error opening the Course data" << endl;
    }
    QTextStream outstream(&file);
    outstream<<courseInfo;

    file.close();
    return("yay");
}

QString dataController::addBook(QString bookInfo) {
    QFile file("../ServerSide/Data/Books.txt");
    if(!file.open(QIODevice::Append))
    {
        qDebug() << "error opening the Book data" << endl;
    }

    QTextStream outstream(&file);
    outstream<<bookInfo;

    file.close();
    return("yay");
}

QString dataController::addChapter(QString chapterInfo) {
    QFile file("../ServerSide/Data/Chapters.txt");
    if(!file.open(QIODevice::Append))
    {
        qDebug() << "error opening the Chapter data" << endl;
    }

    QTextStream outstream(&file);
    outstream<<chapterInfo;

    file.close();
    return("yay");
}

QString dataController::addSection(QString sectionInfo) {
    QFile file("../ServerSide/Data/Sections.txt");
    if(!file.open(QIODevice::Append))
    {
        qDebug() << "error opening the Section data" << endl;
    }

    QTextStream outstream(&file);
    outstream<<sectionInfo;

    file.close();
    return("yay");
}

QString dataController::addSubContent(QString data){
    //Book|2|1
    QStringList dataSplit = data.split("|");
    QString dataType    = dataSplit[0];
    QString dataID      = dataSplit[1];
    QString parentID    = dataSplit[2];
    QString temp;

    QString toAdd       = ",";
    toAdd.append(dataID);


    //----add Book to Course----
    if(dataType.compare("Book")==0){
        QFile file("../ServerSide/Data/Courses.txt");


        if(!file.open(QIODevice::ReadWrite))
        {
            qDebug() << "error opening the Course data" << endl;
        }


        QStringList lines = QStringList(); //temp list of whole file
        lines.append(file.readLine());

        while (!file.atEnd()){
            temp = QString(file.readLine());
            QStringList parentInfo  = temp.split("|");
            int tempSize = parentInfo.size();
            bool isFirst = false;
            if(parentInfo.at(tempSize - 1).isEmpty())
            {
                isFirst = true;
            }
            if(parentID == parentInfo.at(0))
            {
                temp = temp.simplified();
                if(isFirst)
                {
                    temp.append(dataID).append("\n");
                } else {
                    temp.append(toAdd).append("\n");
                }
            }
            lines.append(temp);

        }

        file.close();
        QFile ofile("../ServerSide/Data/newCourses.txt");
        if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
            qDebug()<<"error opening new courses"<<endl;
            return QString("fail");
        }
        QTextStream outstream(&ofile);
        for(int i = 0; i < lines.size(); i++){
            outstream<<lines.at(i);
        }
        ofile.close();

        file.remove();
        ofile.rename("../ServerSide/Data/newCourses.txt","../ServerSide/Data/Courses.txt");



        //----add Chapter to Book----
    } else if(dataType.compare("Chapter")==0) {

        QFile file("../ServerSide/Data/Books.txt");


        if(!file.open(QIODevice::ReadWrite))
        {
            qDebug() << "error opening the Book data" << endl;
        }


        QStringList lines = QStringList(); //temp list of whole file
        lines.append(file.readLine());

        while (!file.atEnd()){
            temp = QString(file.readLine());
            QStringList parentInfo  = temp.split("|");
            int tempSize = parentInfo.size();
            bool isFirst = false;
            if(parentInfo.at(tempSize - 1).isEmpty())
            {
                isFirst = true;
            }
            if(parentID == parentInfo.at(0))
            {
                temp = temp.simplified();
                if(isFirst)
                {
                    temp.append(dataID).append("\n");
                } else {
                    temp.append(toAdd).append("\n");
                }
            }
            lines.append(temp);
        }

        file.close();
        QFile ofile("../ServerSide/Data/newBooks.txt");
        if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
            qDebug()<<"error opening new books"<<endl;
            return QString("fail");
        }
        QTextStream outstream(&ofile);
        for(int i = 0; i < lines.size(); i++){
            outstream<<lines.at(i);
        }
        ofile.close();

        file.remove();
        ofile.rename("../ServerSide/Data/newBooks.txt","../ServerSide/Data/Books.txt");


        //----add Section to Chapter----
    } else if (dataType.compare("Section")==0) {
        QFile file("../ServerSide/Data/Chapters.txt");


        if(!file.open(QIODevice::ReadWrite))
        {
            qDebug() << "error opening the Chapter data" << endl;
        }


        QStringList lines = QStringList(); //temp list of whole file
        lines.append(file.readLine());

        while (!file.atEnd()){
            temp = QString(file.readLine());
            QStringList parentInfo  = temp.split("|");
            int tempSize = parentInfo.size();
            bool isFirst = false;
            if(parentInfo.at(tempSize - 1).isEmpty())
            {
                isFirst = true;
            }
            if(parentID == parentInfo.at(0))
            {
                temp = temp.simplified();
                if(isFirst)
                {
                    temp.append(dataID).append("\n");
                } else {
                    temp.append(toAdd).append("\n");
                }
            }
            lines.append(temp);
        }

        file.close();
        QFile ofile("../ServerSide/Data/newChapters.txt");
        if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
            qDebug()<<"error opening new chapters"<<endl;
            return QString("fail");
        }
        QTextStream outstream(&ofile);
        for(int i = 0; i < lines.size(); i++){
            outstream<<lines.at(i);
        }
        ofile.close();

        file.remove();
        ofile.rename("../ServerSide/Data/newChapters.txt","../ServerSide/Data/Book.txt");



    } else {
        return("Bad Data Type");
    }

    return("added to parent");
}

QString dataController::editContent(QString content){
    //Book|2|newtitle|newprice
       QStringList dataSplit = content.split("|");
       QString dataType    = dataSplit[0];
       QString dataID      = dataSplit[1];
       QString newTitle    = dataSplit[2];
       QString newPrice    = dataSplit[3];
       QString temp;

       //edit book
       if(dataType.compare("Book")==0) {

              QFile file("../ServerSide/Data/Books.txt");


              if(!file.open(QIODevice::ReadWrite))
              {
                  qDebug() << "error opening the Book data" << endl;
              }


              QStringList lines = QStringList(); //temp list of whole file
              lines.append(file.readLine());

              while (!file.atEnd()){
                  temp = QString(file.readLine());
                  QStringList parentInfo  = temp.split("|");

                  if(dataID != parentInfo.at(0))
                  {
                      lines.append(temp);
                  } else {
                      lines.append(dataID.append("|").append(newTitle).append("|").append(newPrice).append("|").append(parentInfo.at(3)));
                  }

              }

              file.close();
              QFile ofile("../ServerSide/Data/newBooks.txt");
              if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
                  qDebug()<<"error opening new books"<<endl;
                  return QString("fail");
              }
              QTextStream outstream(&ofile);
              for(int i = 0; i < lines.size(); i++){
                  outstream<<lines.at(i);
              }
              ofile.close();

              file.remove();
              ofile.rename("../ServerSide/Data/newBooks.txt","../ServerSide/Data/Books.txt");


              //----edit Chapter----
          } else if (dataType.compare("Chapter")==0) {
              QFile file("../ServerSide/Data/Chapters.txt");


              if(!file.open(QIODevice::ReadWrite))
              {
                  qDebug() << "error opening the Chapter data" << endl;
              }


              QStringList lines = QStringList(); //temp list of whole file
              lines.append(file.readLine());

              while (!file.atEnd()){
                  temp = QString(file.readLine());
                  QStringList parentInfo  = temp.split("|");

                  if(dataID != parentInfo.at(0))
                  {
                      lines.append(temp);
                  }else {
                      lines.append(dataID.append("|").append(newTitle).append("|").append(newPrice).append("|").append(parentInfo.at(3)));
                  }
              }

              file.close();
              QFile ofile("../ServerSide/Data/newChapters.txt");
              if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
                  qDebug()<<"error opening new chapters"<<endl;
                  return QString("fail");
              }
              QTextStream outstream(&ofile);
              for(int i = 0; i < lines.size(); i++){
                  outstream<<lines.at(i);
              }
              ofile.close();

              file.remove();
              ofile.rename("../ServerSide/Data/newChapters.txt","../ServerSide/Data/Chapters.txt");


              //----edit Section ----
          } else if (dataType.compare("Section")==0) {
              QFile file("../ServerSide/Data/Sections.txt");


              if(!file.open(QIODevice::ReadWrite))
              {
                  qDebug() << "error opening the Section data" << endl;
              }


              QStringList lines = QStringList(); //temp list of whole file
              lines.append(file.readLine());

              while (!file.atEnd()){
                  temp = QString(file.readLine());
                  QStringList parentInfo  = temp.split("|");

                  if(dataID != parentInfo.at(0))
                  {
                      lines.append(temp);
                  }else {
                      lines.append(dataID.append("|").append(newTitle).append("|").append(newPrice).append("|").append(parentInfo.at(3)));
                  }
              }

              file.close();
              QFile ofile("../ServerSide/Data/newSections.txt");
              if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
                  qDebug()<<"error opening new chapters"<<endl;
                  return QString("fail");
              }
              QTextStream outstream(&ofile);
              for(int i = 0; i < lines.size(); i++){
                  outstream<<lines.at(i);
              }
              ofile.close();

              file.remove();
              ofile.rename("../ServerSide/Data/newSections.txt","../ServerSide/Data/Sections.txt");

          } else {
              return("Bad Data Type");
          }

          return("item deleted");
}

QString dataController::deleteContent(QString content){
    //Book|2
    QStringList dataSplit = content.split("|");
    QString dataType    = dataSplit[0];
    QString dataID      = dataSplit[1];

    QString temp;



        //----delete Book----
    if(dataType.compare("Book")==0) {

        QFile file("../ServerSide/Data/Books.txt");


        if(!file.open(QIODevice::ReadWrite))
        {
            qDebug() << "error opening the Book data" << endl;
        }


        QStringList lines = QStringList(); //temp list of whole file
        lines.append(file.readLine());

        while (!file.atEnd()){
            temp = QString(file.readLine());
            QStringList parentInfo  = temp.split("|");

            if(dataID != parentInfo.at(0))
            {
                lines.append(temp);
            }

        }

        file.close();
        QFile ofile("../ServerSide/Data/newBooks.txt");
        if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
            qDebug()<<"error opening new books"<<endl;
            return QString("fail");
        }
        QTextStream outstream(&ofile);
        for(int i = 0; i < lines.size(); i++){
            outstream<<lines.at(i);
        }
        ofile.close();

        file.remove();
        ofile.rename("../ServerSide/Data/newBooks.txt","../ServerSide/Data/Books.txt");


        //----delete Chapter----
    } else if (dataType.compare("Chapter")==0) {
        QFile file("../ServerSide/Data/Chapters.txt");


        if(!file.open(QIODevice::ReadWrite))
        {
            qDebug() << "error opening the Chapter data" << endl;
        }


        QStringList lines = QStringList(); //temp list of whole file
        lines.append(file.readLine());

        while (!file.atEnd()){
            temp = QString(file.readLine());
            QStringList parentInfo  = temp.split("|");

            if(dataID != parentInfo.at(0))
            {
                lines.append(temp);
            }
        }

        file.close();
        QFile ofile("../ServerSide/Data/newChapters.txt");
        if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
            qDebug()<<"error opening new chapters"<<endl;
            return QString("fail");
        }
        QTextStream outstream(&ofile);
        for(int i = 0; i < lines.size(); i++){
            outstream<<lines.at(i);
        }
        ofile.close();

        file.remove();
        ofile.rename("../ServerSide/Data/newChapters.txt","../ServerSide/Data/Chapters.txt");


        //----delete Section ----
    } else if (dataType.compare("Section")==0) {
        QFile file("../ServerSide/Data/Sections.txt");


        if(!file.open(QIODevice::ReadWrite))
        {
            qDebug() << "error opening the Section data" << endl;
        }


        QStringList lines = QStringList(); //temp list of whole file
        lines.append(file.readLine());

        while (!file.atEnd()){
            temp = QString(file.readLine());
            QStringList parentInfo  = temp.split("|");

            if(dataID != parentInfo.at(0))
            {
                lines.append(temp);
            }
        }

        file.close();
        QFile ofile("../ServerSide/Data/newSections.txt");
        if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
            qDebug()<<"error opening new chapters"<<endl;
            return QString("fail");
        }
        QTextStream outstream(&ofile);
        for(int i = 0; i < lines.size(); i++){
            outstream<<lines.at(i);
        }
        ofile.close();

        file.remove();
        ofile.rename("../ServerSide/Data/newSections.txt","../ServerSide/Data/Sections.txt");

    } else {
        return("Bad Data Type");
    }

    return("item deleted");
}

QString dataController::getAllCourse()
{
    QFile file("../ServerSide/Data/Courses.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening the data" << endl;
    }
    QString courseString = QString(file.readLine());  //skip the first useless line
    QString result = "";
    while(!file.atEnd())
    {
        courseString = QString(file.readLine()).simplified();
        result.append(courseString).append(":");
    }
    file.close();
    return result;
}

QString dataController::editCourse(QString content){
    QStringList datasplit = content.split("|");
    QString cID       = datasplit[0];
    QString newTitle  = datasplit[1];
    QString temp;
    QFile file("../ServerSide/Data/Courses.txt");


    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "error opening the Course data" << endl;
    }


    QStringList lines = QStringList(); //temp list of whole file
    lines.append(file.readLine());

    while (!file.atEnd()){
        temp = QString(file.readLine());
        QStringList parentInfo  = temp.split("|");

        if(cID != parentInfo.at(0))
        {
            lines.append(temp);
        } else {
            lines.append(cID.append("|").append(newTitle).append("|").append(parentInfo.at(2)));
        }

    }

    file.close();
    QFile ofile("../ServerSide/Data/newCourses.txt");
    if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
        qDebug()<<"error opening new Courses"<<endl;
        return QString("fail");
    }
    QTextStream outstream(&ofile);
    for(int i = 0; i < lines.size(); i++){
        outstream<<lines.at(i);
    }
    ofile.close();

    file.remove();
    ofile.rename("../ServerSide/Data/newCourses.txt","../ServerSide/Data/Courses.txt");
}

QString dataController::deleteCourse(QString course){
    QString cID = course;
    QString temp;
    QFile file("../ServerSide/Data/Courses.txt");


    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "error opening the Course data" << endl;
    }


    QStringList lines = QStringList(); //temp list of whole file
    lines.append(file.readLine());

    while (!file.atEnd()){
        temp = QString(file.readLine());
        QStringList parentInfo  = temp.split("|");

        if(cID != parentInfo.at(0))
        {
            lines.append(temp);
        }

    }

    file.close();
    QFile ofile("../ServerSide/Data/newCourses.txt");
    if(!ofile.open(QIODevice::ReadWrite|QIODevice::Text)){
        qDebug()<<"error opening new Courses"<<endl;
        return QString("fail to open");
    }
    QTextStream outstream(&ofile);
    for(int i = 0; i < lines.size(); i++){
        outstream<<lines.at(i);
    }
    ofile.close();

    file.remove();
    ofile.rename("../ServerSide/Data/newCourses.txt","../ServerSide/Data/Courses.txt");
}
