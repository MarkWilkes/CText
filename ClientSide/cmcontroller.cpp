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

    //addContent page
    connect(ui->submit_button, SIGNAL(clicked()), this, SLOT(submitButtonClicked()));
    connect(ui->cancel_button, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
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
            QTreeWidgetItem *bookWidget = addRoot(BookName,BookPrice);
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
                    QTreeWidgetItem *chapterWidget = addChild(bookWidget,ChapterName, ChapterPrice);
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
                            addChild(chapterWidget, SectionName, SectionPrice);
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

void CmController::editContentButtonClicked() {

}

QTreeWidgetItem* CmController::addRoot(QString name, QString price)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->CmViewList);
    item->setText(0,name);
    item->setText(1,price);
    return item;
}

QTreeWidgetItem* CmController::addChild(QTreeWidgetItem *parent, QString name, QString price)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,name);
    item->setText(1,price);
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
        QString bookID, bookTitle, bookPrice;
        bookID = c->sendRequest("nextIDRequest|", temp.append("|").append("Book"));
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
            c->sendRequest("addXtoYRequest|", temp.append("|").append("Book|").append(bookID).append("|").append(ownerID));
        }

    //---ADD CHAPTER---
    } else if(ui->chapter_radioButton->isChecked()) {
        QString chapterInfo = "";

        //get chapter info
        QString chapterID, chapterTitle, chapterPrice;
        chapterID = c->sendRequest("nextIDRequest|", temp.append("|").append("Chapter"));
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
            c->sendRequest("addXtoYRequest|", temp.append("|").append("Chapter|").append(chapterID).append("|").append(ownerID));
        }

    //---ADD SECTION---
    } else if(ui->section_radioButton->isChecked()) {
        QString sectionInfo = "";

        //get chapter info
        QString sectionID, sectionTitle, sectionPrice;
        sectionID = c->sendRequest("nextIDRequest|", temp.append("|").append("Section"));
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
            c->sendRequest("addXtoYRequest|", temp.append("|").append("Section|").append(sectionID).append("|").append(ownerID));
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


