#include "cmcontroller.h"

CmController::CmController(QObject *parent, ClientConnection *cClient, Ui::MainWindow *uiMainWindow) :
    QObject(parent)
{
    ui = uiMainWindow;
    c = cClient;

    //main Cm window
    connect(ui->viewContent_button, SIGNAL(clicked()), this, SLOT(viewContentButtonClicked()));
    connect(ui->addContent_button, SIGNAL(clicked()), this, SLOT(addContentButtonClicked()));
    connect(ui->editContent_button, SIGNAL(clicked()), this, SLOT(editContentButtonClicked()));
    connect(ui->CmViewList, SIGNAL(itemSelectionChanged()),this, SLOT(CMViewListChanged()));

    connect(ui->viewCourse_button, SIGNAL(clicked()), this, SLOT(viewCourseButtonClicked()));
    connect(ui->addCourse_button, SIGNAL(clicked()), this, SLOT(addCourseButtonClicked()));
    connect(ui->editCourse_button, SIGNAL(clicked()), this, SLOT(editCourseButtonClicked()));
    connect(ui->CmViewList_2, SIGNAL(itemSelectionChanged()),this, SLOT(CMCourseListChanged()));

    //addContent page
    connect(ui->submit_button, SIGNAL(clicked()), this, SLOT(submitButtonClicked()));
    connect(ui->cancel_button, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

    //editContent page
    connect(ui->editSubmit_button, SIGNAL(clicked()), this, SLOT(editSubmitButtonClicked()));
    connect(ui->editCancel_button, SIGNAL(clicked()), this, SLOT(editCancelButtonClicked()));
    connect(ui->editDelete_button, SIGNAL(clicked()), this, SLOT(editDeleteButtonClicked()));

    //addCourse page
    connect(ui->addCourseSubmit_button, SIGNAL(clicked()), this, SLOT(addCourseSubmitButtonClicked()));
    connect(ui->addCourseCancel_button, SIGNAL(clicked()), this, SLOT(addCourseCancelButtonClicked()));

    //editCourse page
    connect(ui->editSubmit_button_2, SIGNAL(clicked()), this, SLOT(editCourseSubmitButtonClicked()));
    connect(ui->editCancel_button_2, SIGNAL(clicked()), this, SLOT(editCourseCancelButtonClicked()));
    connect(ui->editDelete_button_2, SIGNAL(clicked()), this, SLOT(editCourseDeleteButtonClicked()));

}

void CmController::initialize(QString uID)
{
    this->userID = uID;
    ui->stackedWidget->setCurrentIndex(2);
    ui->userID->setText(userID);
}

void CmController::viewContentButtonClicked() {

    ui->CmViewList->clear();
    QString temp = userID;
    //get num books
    QString bookNumString = c->sendRequest("nextIDRequest|", temp.append("|").append("Book"));
    int numBooks = bookNumString.toInt();
    QString nextBook;

    for(int j = 1; j < numBooks; j++)
    {
        temp = userID;
        nextBook = QString::number(j);//Book|1
        QString bookInfos = c->sendRequest("getBookInfoRequest|",
                                           temp.append("|").append(nextBook));
        if(bookInfos == "empty")
        {
            continue;

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
            QTreeWidgetItem *bookWidget = addRoot(BookID,BookName,BookPrice);
            QStringList chapterIDs = ChapterList.split(",");
            for(int k = 0; k < chapterIDs.size(); k++)
            {
                QString temp = userID;
                QString chapterInfos = c->sendRequest("getChapterInfoRequest|",
                                                      temp.append("|").append(chapterIDs[k]));
                if(chapterInfos == "empty")
                {
                    //no chapters found

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
                    QTreeWidgetItem *chapterWidget = addChild(bookWidget,ChapterID,ChapterName, ChapterPrice);
                    QStringList sectionIDs = SectionList.split(",");
                    for(int l = 0; l < sectionIDs.size(); l++)
                    {
                        QString temp = userID;
                        QString sectionInfos = c->sendRequest("getSectionInfoRequest|",
                                                              temp.append("|").append(sectionIDs[l]));
                        if(sectionInfos == "empty")
                        {

                            //no sections found

                        } else if(sectionInfos == "fail") {

                            emit sendMsg("critical", "User haven't logged in or don't have the privilege!");

                        } else {
                            QStringList sectionInfo = sectionInfos.split("|");
                            QString SectionID = sectionInfo[0];
                            QString SectionName = sectionInfo[1];
                            QString SectionPrice = sectionInfo[2];
                            Section *section = new Section(SectionID, SectionName, SectionPrice);
                            chapter->addSection(section);
                            addChild(chapterWidget, SectionID, SectionName, SectionPrice);
                        }
                    }
                }
            }

        }
    }
}

void CmController::addContentButtonClicked() {
    ui->stackedWidget->setCurrentIndex(3);
}

QTreeWidgetItem* CmController::addRoot(QString ID, QString name, QString price)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->CmViewList);
    item->setText(0,ID);
    item->setText(1,name);
    item->setText(2,price);
    return item;
}

QTreeWidgetItem* CmController::addChild(QTreeWidgetItem *parent,QString ID, QString name, QString price)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,ID);
    item->setText(1,name);
    item->setText(2,price);
    parent->addChild(item);
    return item;
}

void CmController::submitButtonClicked() {
    ui->error_label->setText("");


    QString result;
    QString temp = userID;

    //check for blanks
    if(ui->title_textbox->text().isEmpty()){
        ui->error_label->setText("Fill in Title/Price fields");
        return;

    //---ADD BOOK---
    } else if(ui->book_radioButton->isChecked()) {
        QString bookInfo = "";

        //get book info
        QString bookID, bookTitle, bookPrice, x;
        bookID = c->sendRequest("nextIDRequest|", temp.append("|").append("Book"));
        x = bookID;
        bookTitle = ui->title_textbox->text();
        bookPrice = ui->price_input->text();

        //make book info
        bookInfo = bookID.append("|").append(bookTitle).append("|").append(bookPrice).append("|");

        //send
        result = c->sendRequest("addBookRequest|", temp.append("|").append(bookInfo));

        //add to course(optional)
        if (!ui->owner_textbox->text().isEmpty()){
            temp = userID;
            QString ownerID = ui->owner_textbox->text();
            c->sendRequest("addXtoYRequest|", temp.append("|").append("Book|").append(x).append("|").append(ownerID));
        }

    //---ADD CHAPTER---
    } else if(ui->chapter_radioButton->isChecked()) {
        QString chapterInfo = "";

        //get chapter info
        QString chapterID, chapterTitle, chapterPrice,y;
        chapterID = c->sendRequest("nextIDRequest|", temp.append("|").append("Chapter"));
        y = chapterID;
        chapterTitle = ui->title_textbox->text();
        chapterPrice = ui->price_input->text();

        //make chapter info
        chapterInfo = chapterID.append("|").append(chapterTitle).append("|").append(chapterPrice).append("|");

        //send
        result = c->sendRequest("addChapterRequest|", temp.append("|").append(chapterInfo));

        //add to book(optional?)
        if (!ui->owner_textbox->text().isEmpty()){
            temp = userID;
            QString ownerID = ui->owner_textbox->text();
            c->sendRequest("addXtoYRequest|", temp.append("|").append("Chapter|").append(y).append("|").append(ownerID));
        }

    //---ADD SECTION---
    } else if(ui->section_radioButton->isChecked()) {
        QString sectionInfo = "";

        //get chapter info
        QString sectionID, sectionTitle, sectionPrice, z;
        sectionID = c->sendRequest("nextIDRequest|", temp.append("|").append("Section"));
        z = sectionID;
        sectionTitle = ui->title_textbox->text();
        sectionPrice = ui->price_input->text();

        //make chapter info
        sectionInfo = sectionID.append("|").append(sectionTitle).append("|").append(sectionPrice).append("|");

        //send
        result = c->sendRequest("addSectionRequest|", temp.append("|").append(sectionInfo));

        //add to Chapter(optional?)
        if (!ui->owner_textbox->text().isEmpty()){
            temp = userID;
            QString ownerID = ui->owner_textbox->text();
            c->sendRequest("addXtoYRequest|", temp.append("|").append("Section|").append(z).append("|").append(ownerID));
        }

    }

    viewContentButtonClicked();
    cancelButtonClicked();
}

void CmController::cancelButtonClicked() {

    //clear and return
    ui->title_textbox->clear();
    ui->price_input->clear();
    ui->owner_textbox->clear();
    ui->book_radioButton->click();
    ui->stackedWidget->setCurrentIndex(2);

}

void CmController::editContentButtonClicked() {

    //make sure something is selected
    if (ui->CmViewList->selectedItems().isEmpty()) {
        //no items selected, go away
    } else {
        //get info for item
        QList<QTreeWidgetItem *> items = ui->CmViewList->selectedItems();
        QString itemType, itemID, itemTitle, itemPrice;

        for(int i = 0; i < items.size(); i++)
        {
            if(items[i]->parent() == 0)
            {
                //this is a book
                itemID = items[i]->text(0);
                itemTitle = items[i]->text(1);
                itemPrice = items[i]->text(2);
                itemType = "Book";
                continue;
            }
            if(items[i]->parent()->parent() == 0)
            {
                //this is a chapter
                itemID = items[i]->text(0);
                itemTitle = items[i]->text(1);
                itemPrice = items[i]->text(2);
                itemType = "Chapter";
                continue;
            }
            if(items[i]->parent()->parent()->parent() == 0)
            {
                //this is a section
                itemID = items[i]->text(0);
                itemTitle = items[i]->text(1);
                itemPrice = items[i]->text(2);
                itemType = "Section";
                continue;
            }
        }

        //set up and go to edit page
        ui->stackedWidget->setCurrentIndex(4);
        ui->editID_label->setText(itemID);
        ui->oldTitle_label->setText(itemTitle);
        ui->oldPrice_label->setText(itemPrice);        
        ui->label_8->setText(itemType);
    }

}

void CmController::CMViewListChanged()
{
    QList<QTreeWidgetItem *> items = ui->CmViewList->selectedItems();
    for(int i = 0; i < items.size(); i++){
        ui->editContent_button->setEnabled(true);
    }
}

void CmController::CMCourseListChanged()
{
    QList<QTreeWidgetItem *> items = ui->CmViewList_2->selectedItems();
    for(int i = 0; i < items.size(); i++){
        ui->editCourse_button->setEnabled(true);
    }
}

void CmController::editSubmitButtonClicked() {
    QString temp = userID;
    QString type, ID, newName, newPrice;
    type      = ui->label_8->text();
    ID        = ui->editID_label->text();
    newName   = ui->newTitle_textbox->text();
    newPrice  = ui->newPrice_input->text();

    //editContent|uri|Book|1|newtitle|newprice
    c->sendRequest("editContent|", temp.append("|").append(type).append("|").append(ID).append("|").append(newName).append("|").append(newPrice));

    viewContentButtonClicked();
    editCancelButtonClicked();
}

void CmController::editDeleteButtonClicked() {
    QString temp = userID;
    QString type, ID;
    ID      = ui->editID_label->text();
    type    = ui->label_8->text();
    //deleteContent|uri|Book|1
    c->sendRequest("deleteContent|", temp.append("|").append(type).append("|").append(ID));

    viewContentButtonClicked();
    editCancelButtonClicked();
}

void CmController::editCancelButtonClicked() {

    //clear and return
    ui->newTitle_textbox->clear();
    ui->newPrice_input->clear();
    ui->stackedWidget->setCurrentIndex(2);
}

void CmController::viewCourseButtonClicked(){

    ui->CmViewList_2->clear();
    //get num books
    QString courseString = c->sendRequest("getAllCourse|", userID);
    QStringList courses = courseString.split(":", QString::SkipEmptyParts);    //COMP3004|Object-Oriented Software Engineer|1,2,3
                                                                                //COMP3000|Operating Systems|4,6
    for(int j = 0; j < courses.size(); j++)
    {
        QStringList courseInfo = courses.at(j).split("|");
        QString CourseID, CourseName;
        CourseID = courseInfo[0];
        CourseName = courseInfo[1];
        addCourse(CourseID,CourseName);
    }
}

void CmController::addCourseButtonClicked(){
    ui->stackedWidget->setCurrentIndex(5);
}

void CmController::editCourseButtonClicked(){
    //make sure something is selected
        if (ui->CmViewList_2->selectedItems().isEmpty()) {
            //no items selected, go away
        } else {
            //get info for item
            QList<QTreeWidgetItem *> items = ui->CmViewList_2->selectedItems();
            QString itemID, itemTitle;
            for(int i = 0; i < items.size(); i++)
            {
                if(items[i]->parent() == 0)
                {
                    itemID = items[i]->text(0);
                    itemTitle = items[i]->text(1);
                }
            }

            //set up and go to edit page
            ui->stackedWidget->setCurrentIndex(6);
            ui->courseEditID_label->setText(itemID);
            ui->courseOldTitle_label->setText(itemTitle);
        }
}

void CmController::addCourseSubmitButtonClicked(){
       ui->error_label_2->setText("");
       QString courseID, courseTitle;
       QString temp = userID;

       if (ui->addCourseID_textbox->text().isEmpty() || ui->addCourseTitle_textbox->text().isEmpty()){
           ui->error_label_2->setText("Fill in ID/Title fields");

       } else {
           courseID = ui->addCourseID_textbox->text();
           courseTitle = ui->addCourseTitle_textbox->text();
           c->sendRequest("addCourseRequest|",temp.append("|").append(courseID).append("|").append(courseTitle).append("|"));

           addCourseCancelButtonClicked();
           viewCourseButtonClicked();
       }
}

void CmController::addCourseCancelButtonClicked(){

    ui->addCourseID_textbox->clear();
    ui->addCourseTitle_textbox->clear();
    ui->error_label_2->setText("");
    ui->stackedWidget->setCurrentIndex(2);
}

void CmController::editCourseSubmitButtonClicked(){
    QString temp = userID;
    QString ID, newTitle;
    ID        = ui->courseEditID_label->text();
    newTitle   = ui->newCourseTitle_textbox->text();

    //editCourse|uri|comp3000|newtitle
    c->sendRequest("editCourseRequest|", temp.append("|").append(ID).append("|").append(newTitle));

    viewCourseButtonClicked();
    editCancelButtonClicked();
}

void CmController::editCourseDeleteButtonClicked(){
    QString temp    = userID;
    QString ID      = ui->courseEditID_label->text();

    //deleteCourse|uri|comp3000
    c->sendRequest("deleteCourseRequest|", temp.append("|").append(ID));

    viewCourseButtonClicked();
    editCancelButtonClicked();
}

void CmController::editCourseCancelButtonClicked(){
    ui->newCourseTitle_textbox->clear();
    ui->stackedWidget->setCurrentIndex(2);
}

QTreeWidgetItem *CmController::addCourse(QString courseID, QString courseName)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->CmViewList_2);
    item->setText(0,courseID);
    item->setText(1,courseName);
    return item;
}
