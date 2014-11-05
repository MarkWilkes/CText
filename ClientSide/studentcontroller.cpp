#include "studentcontroller.h"

StudentController::StudentController(QObject *parent, ClientConnection *cClient, Ui::MainWindow *uiMainWindow) :
    QObject(parent)
{
    ui = uiMainWindow;
    c = cClient;

    connect(ui->viewCourses_button, SIGNAL(clicked()), this, SLOT(viewCourseButtonClicked()));
    connect(ui->addItem_button, SIGNAL(clicked()),this, SLOT(addCartButtonClicked()));
    connect(ui->viewShoppingCart_button, SIGNAL(clicked()),this, SLOT(shoppingCartButtonClicked()));
    connect(ui->placeOrder_button,SIGNAL(clicked()),this, SLOT(placeOrderButtonClicked()));
    connect(ui->cancelOrder_button, SIGNAL(clicked()), this, SLOT(cancelOrderButtonClicked()));
    connect(ui->studentViewList, SIGNAL(itemSelectionChanged()),this, SLOT(studentViewListChanged()));
}

void StudentController::initialize(QString studentID)
{
    this->studentID = studentID;
    ui->stackedWidget->setCurrentIndex(1);
    ui->studentID->setText(studentID);
}

void StudentController::viewCourseButtonClicked()
{
    ui->studentViewList->clear();
    QString coursesNum = c->sendRequest("getRegistedCourseRequest|", studentID);
    if(coursesNum == "empty")
    {

        emit sendMsg("critical", "Student don't have registed course!");

    } else if(coursesNum == "fail") {

        emit sendMsg("critical", "User haven't logged in or don't have the privilege!");

    } else {
        ui->cancelOrder_button->setEnabled(false);
        ui->placeOrder_button->setEnabled(false);

        QStringList coursesInfo = coursesNum.split("|", QString::SkipEmptyParts);
        //count the number of courses that the studend have
        int courseCount = coursesInfo.size()/3;
        for(int i = 0; i < courseCount; i++)
        {
            QString CourseID,CourseName,BookList;
            CourseID = coursesInfo[i*3+0];
            CourseName = coursesInfo[i*3+1];
            BookList = coursesInfo[i*3+2];
            Course *course = new Course(CourseID, CourseName);
            courses.push_back(course);
            //set the value to the gui
            QTreeWidgetItem *courseWidget = addRoot(CourseName, "");
            QStringList BookIDs = BookList.split(",");
            for(int j = 0; j < BookIDs.size(); j++)
            {
                QString temp = studentID;
                QString bookInfos = c->sendRequest("getBookInfoRequest|",
                                                   temp.append("|").append(BookIDs[j]));
                if(bookInfos == "empty")
                {

                    emit sendMsg("critical", "Cannot find corresponding book from the Book ID!");

                } else if(bookInfos == "fail") {

                    emit sendMsg("critical", "User haven't logged in or don't have the privilege!");

                } else {
                    QStringList bookInfo = bookInfos.split("|");
                    QString BookID, BookName, BookPrice, ChapterList;
                    BookID = bookInfo[0];
                    BookName = bookInfo[1];
                    BookPrice = bookInfo[2];
                    ChapterList = bookInfo[3];
                    Book *book = new Book(BookID, BookName, BookPrice);
                    course->addBook(book);
                    QTreeWidgetItem *bookWidget = addChild(courseWidget,BookName,BookPrice);
                    QStringList chapterIDs = ChapterList.split(",");
                    for(int k = 0; k < chapterIDs.size(); k++)
                    {
                        QString temp = studentID;
                        QString chapterInfos = c->sendRequest("getChapterInfoRequest|",
                                                              temp.append("|").append(chapterIDs[k]));
                        if(chapterInfos == "empty")
                        {

                            emit sendMsg("critical", "Cannot find corresponding chapter from the chapter ID!");

                        } else if(chapterInfos == "fail") {

                            emit sendMsg("critical", "User haven't logged in or don't have the privilege!");

                        } else {
                            QStringList chapterInfo = chapterInfos.split("|");
                            QString ChapterID = chapterInfo[0];
                            QString ChapterName = chapterInfo[1];
                            QString ChapterPrice = chapterInfo[2];
                            QString SectionList = chapterInfo[3];
                            Chapter *chapter = new Chapter(ChapterID, ChapterName, ChapterPrice);
                            book->addChapter(chapter);
                            QTreeWidgetItem *chapterWidget = addChild(bookWidget,ChapterName, ChapterPrice);
                            QStringList sectionIDs = SectionList.split(",");
                            for(int l = 0; l < sectionIDs.size(); l++)
                            {
                                QString temp = studentID;
                                QString sectionInfos = c->sendRequest("getSectionInfoRequest|",
                                                                      temp.append("|").append(sectionIDs[l]));
                                if(sectionInfos == "empty")
                                {

                                    emit sendMsg("critical", "Cannot find corresponding section from the Section ID!");

                                } else if(sectionInfos == "fail") {

                                    emit sendMsg("critical", "User haven't logged in or don't have the privilege!");

                                } else {
                                    QStringList sectionInfo = sectionInfos.split("|");
                                    QString SectionID = sectionInfo[0];
                                    QString SectionName = sectionInfo[1];
                                    QString SectionPrice = sectionInfo[2];
                                    Section *section = new Section(SectionID, SectionName, SectionPrice);
                                    chapter->addSection(section);
                                    addChild(chapterWidget, SectionName, SectionPrice);
                                }
                            }
                        }
                    }

                }
            }

        }
    }
}

void StudentController::addCartButtonClicked(){
    QList<QTreeWidgetItem *> items = ui->studentViewList->selectedItems();
    for(int i = 0; i < items.size(); i++){
        if(items[i]->parent() == 0){
            //this is a course
            continue;
        }
        if(items[i]->parent()->parent() == 0){
            //this is a book
            QString itemName = items[i]->text(0);
            QString courseName = items[i]->parent()->text(0);
            for(int j = 0; j <courses.size();j++){
                if(courses[j]->getName().compare(courseName) ==0){
                    QList<Book*> books = courses[j]->getBooks();
                    for(int k = 0; k < books.size(); k++){
                        if(books[k]->getName().compare(itemName) == 0){
                            QString temp = studentID;
                            QString response  = c->sendRequest("addBooktoCart|",temp.append("|").append(books[k]->getID()));
                            if(response.compare("already exists") == 0){
                                QMessageBox::information(ui->Main, tr("cuTPS"),tr("Book already in cart"));
                            }
                            qDebug() << itemName<<endl;
                        }
                    }
                }
            }
            continue;
        }
        if(items[i]->parent()->parent()->parent() == 0){
            //this is a chapter
            //qDebug() << "chapter" << endl;
            QString itemName = items[i]->text(0);
            QString bookName = items[i]->parent()->text(0);
            QString courseName = items[i]->parent()->parent()->text(0);
            for(int j = 0; j <courses.size();j++){
                if(courses[j]->getName().compare(courseName) ==0){
                    QList<Book*> books = courses[j]->getBooks();
                    for(int k = 0; k < books.size(); k++){
                        if(books[k]->getName().compare(bookName) == 0){
                            QList<Chapter*> chapters = books[k]->getChapters();
                            for(int l = 0; l < chapters.size(); l++){
                                if(chapters[l]->getName().compare(itemName) == 0){
                                    QString temp = studentID;
                                    QString response = c->sendRequest("addChaptertoCart|",temp.append("|").append(chapters[l]->getID()));
                                    if(response.compare("already exists") == 0){
                                        QMessageBox::information(ui->Main, tr("cuTPS"),tr("Chapter already in cart"));
                                    }
                                    qDebug() << itemName<<endl;
                                }
                            }
                        }
                    }
                }
            }
            continue;
        }
        if(items[i]->parent()->parent()->parent()->parent() == 0){
            //qDebug() << "section" << endl;
            QString itemName = items[i]->text(0);
            QString chapterName = items[i]->parent()->text(0);
            QString bookName = items[i]->parent()->parent()->text(0);
            QString courseName = items[i]->parent()->parent()->parent()->text(0);
            for(int j = 0; j <courses.size();j++){
                if(courses[j]->getName().compare(courseName) ==0){
                    QList<Book*> books = courses[j]->getBooks();
                    for(int k = 0; k < books.size(); k++){
                        if(books[k]->getName().compare(bookName) == 0){
                            QList<Chapter*> chapters = books[k]->getChapters();
                            for(int l = 0; l < chapters.size(); l++){
                                if(chapters[l]->getName().compare(chapterName) == 0){
                                    QList<Section*> sections = chapters[l]->getSections();
                                    for(int m = 0; m < sections.size(); m++){
                                        if(sections[m]->getName().compare(itemName) == 0){
                                            QString temp = studentID;
                                            QString response = c->sendRequest("addSectiontoCart|",temp.append("|").append(sections[m]->getID()));
                                            if(response.compare("already exists") == 0){
                                                QMessageBox::information(ui->Main, tr("cuTPS"),tr("Section already in cart"));
                                            }
                                            qDebug() << itemName<<endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            continue;
        }
    }
}

void StudentController::shoppingCartButtonClicked(){
    ui->studentViewList->clear();

    ui->addItem_button->setEnabled(false);
    QString temp = studentID;
    QString cartID = c->sendRequest("getCartID|",temp);
    if(cartID == "empty"){
        emit sendMsg("critical", "Cannot find corresponding cartID from the studentID");
    }
    else if(cartID == "fail"){
        emit sendMsg("critical", "User haven't logged in or don't have the privilage!");
    }
    else{
        QString cartInfo = c->sendRequest("getCartInfoRequest|",
                                          temp.append("|").append(cartID));
        if(cartInfo == "empty"){

            emit sendMsg("critical", "Cannot find corresponding cart from the Cart ID!");
        }
        else if(cartInfo =="fail"){

            emit sendMsg("critical", "User haven't logged in or don't have the privilege!");
        }
        else{
            ui->cancelOrder_button->setEnabled(true);
            ui->placeOrder_button->setEnabled(true);
            ui->addItem_button->setEnabled(false);

            QStringList cartInfos = cartInfo.split("|");
            QString CartID = cartInfos[0];
            QString CartBooks = cartInfos[1];
            QString CartChapters = cartInfos[2];
            QString CartSections = cartInfos[3];
            Cart * cart = new Cart(CartID);

            if(!CartBooks.isEmpty()){
                QStringList bookList = CartBooks.split(",");
                for(int i = 0; i < bookList.size(); i++){
                    temp = studentID;
                    QString bookInfos = c->sendRequest("getBookInfoRequest|",
                                                       temp.append("|").append(bookList[i]));
                    if(bookInfos == "empty")
                    {
                        emit sendMsg("critical", "Cannot find corresponding book from the Book ID!");

                    } else if(bookInfos == "fail") {

                        emit sendMsg("critical", "User haven't logged in or don't have the privilege!");

                    } else {
                        QStringList bookInfo = bookInfos.split("|");
                        QString BookID, BookName, BookPrice, ChapterList;
                        BookID = bookInfo[0];
                        BookName = bookInfo[1];
                        BookPrice = bookInfo[2];
                        ChapterList = bookInfo[3];
                        Book *book = new Book(BookID, BookName, BookPrice);
                        cart->addBook(book);

                        addRoot(BookName, BookPrice);
                    }
                }
            }
            if(!CartChapters.isEmpty()){
            QStringList chapterList = CartChapters.split(",");
                for(int i = 0; i < chapterList.size(); i++){
                    temp = studentID;
                    QString chapterInfos = c->sendRequest("getChapterInfoRequest|",
                                                       temp.append("|").append(chapterList[i]));
                    if(chapterInfos == "empty")
                    {

                        emit sendMsg("critical", "Cannot find corresponding chapter from the Chapter ID!");

                    } else if(chapterInfos == "fail") {

                        emit sendMsg("critical", "User haven't logged in or don't have the privilege!");

                    } else {
                        QStringList chapterInfo = chapterInfos.split("|");
                        QString ChapterID, ChapterName, ChapterPrice, SectionList;
                        ChapterID = chapterInfo[0];
                        ChapterName = chapterInfo[1];
                        ChapterPrice = chapterInfo[2];
                        SectionList = chapterInfo[3];
                        Chapter *chapter = new Chapter(ChapterID, ChapterName, ChapterPrice);
                        cart->addChapter(chapter);

                        addRoot(ChapterName, ChapterPrice);
                    }
                }
            }
            if(!CartSections.isEmpty()){
                QStringList sectionList = CartSections.split(",");
                for(int i = 0; i < sectionList.size(); i++){
                    temp = studentID;
                    QString sectionInfos = c->sendRequest("getSectionInfoRequest|",
                                                       temp.append("|").append(sectionList[i]));
                    if(sectionInfos == "empty")
                    {

                        emit sendMsg("critical", "Cannot find corresponding section from the Section ID!");

                    } else if(sectionInfos == "fail") {

                        emit sendMsg("critical", "User haven't logged in or don't have the privilege!");

                    } else {
                        QStringList sectionInfo = sectionInfos.split("|");
                        QString sectionID, sectionName, sectionPrice;
                        sectionID = sectionInfo[0];
                        sectionName = sectionInfo[1];
                        sectionPrice = sectionInfo[2];
                        Section *section = new Section(sectionID, sectionName, sectionPrice);
                        cart->addSection(section);

                        addRoot(sectionName, sectionPrice);
                    }
                }
            }
        }
    }
}

void StudentController::placeOrderButtonClicked(){
    ui->studentViewList->clear();
    ui->placeOrder_button->setEnabled(false);
    ui->cancelOrder_button->setEnabled(false);
    QString temp = studentID;
    QString cartID = c->sendRequest("getCartID|",temp);
    if(cartID == "empty"){
        emit sendMsg("critical", "Cannot find corresponding cartID from the studentID");
    }
    else if(cartID == "fail"){
        emit sendMsg("critical", "User haven't logged in or don't have the privilage!");
    }
    else{
        c->sendRequest("setCart|",cartID.append("|||"));
    }
    QMessageBox::information(ui->Main, tr("cuTPS"),tr("Order Placed"));
}

void StudentController::cancelOrderButtonClicked(){
    ui->studentViewList->clear();
    ui->placeOrder_button->setEnabled(false);
    ui->cancelOrder_button->setEnabled(false);
    QString temp = studentID;
    QString cartID = c->sendRequest("getCartID|",temp);
    if(cartID == "empty"){
        emit sendMsg("critical", "Cannot find corresponding cartID from the studentID");
    }
    else if(cartID == "fail"){
        emit sendMsg("critical", "User haven't logged in or don't have the privilage!");
    }
    else{
        c->sendRequest("setCart|",cartID.append("|||"));
    }
    QMessageBox::information(ui->Main, tr("cuTPS"),tr("Order Cancelled"));
}

void StudentController::studentViewListChanged(){
    if(ui->placeOrder_button->isEnabled()){
        return;
    }
    QList<QTreeWidgetItem *> items = ui->studentViewList->selectedItems();
    for(int i = 0; i < items.size(); i++){
        if(items[i]->parent() == 0){
            ui->addItem_button->setEnabled(false);
        }
        else{
            ui->addItem_button->setEnabled(true);
        }
    }
}

QTreeWidgetItem* StudentController::addRoot(QString name, QString price)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->studentViewList);
    item->setText(0,name);
    item->setText(1,price);
    return item;
}

QTreeWidgetItem* StudentController::addChild(QTreeWidgetItem *parent, QString name, QString price)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,name);
    item->setText(1,price);
    parent->addChild(item);
    return item;
}
