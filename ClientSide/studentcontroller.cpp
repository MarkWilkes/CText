#include "studentcontroller.h"

StudentController::StudentController(QObject *parent, ClientConnection *cClient, Ui::MainWindow *uiMainWindow) :
    QObject(parent)
{
    ui = uiMainWindow;
    c = cClient;

    connect(ui->viewCourses_button, SIGNAL(clicked()), this, SLOT(viewCourseButtonClicked()));
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
                    if(ChapterList != "")
                    {
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
                                if(SectionList != "")
                                {
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
