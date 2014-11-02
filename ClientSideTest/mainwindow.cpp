#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_3->setReadOnly(true);
    c = new ClientConnection();
}

void MainWindow::clearTest()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit_2->clear();
    ui->plainTextEdit_3->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    clearTest();

    QString testDescription = "This test case view the course list for student 'frank'\r\n";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedValue = "CourseID : COMP3004 \r\nCourseName : Object-Oriented Software Engineer";
    ui->plainTextEdit_2->appendPlainText(expectedValue);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system \r\n");

    //get the Registed Course for frank
    QString coursesNum = c->sendRequest("getRegistedCourseRequest|", "frank");
    QStringList coursesInfo = coursesNum.split("|", QString::SkipEmptyParts);
    int courseCount = coursesInfo.size()/3;
    for(int i = 0; i < courseCount; i++)
    {
        QString courseID = coursesInfo[i*3 + 0];
        QString courseName = coursesInfo[i*3 + 1];
        ui->plainTextEdit_3->appendPlainText(QString("CourseID : ").append(courseID));
        ui->plainTextEdit_3->appendPlainText(QString("CourseName : ").append(courseName));
        if(courseID == "COMP3004" && courseName == "Object-Oriented Software Engineer")
        {
            ui->plainTextEdit_3->appendPlainText("Test case passed\r\n");
        } else {
            ui->plainTextEdit_3->appendPlainText("Test case failed\r\n");
        }
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank login out the system \r\n\r\n");
}

void MainWindow::on_pushButton_2_clicked()
{
    clearTest();

    QString testDescription = "This test case check the book information from book ID\r\n";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedValue = "BookID : 1\r\nBookName : helloworld\r\nBookPrice : 10.99\r\n";
    ui->plainTextEdit_2->appendPlainText(expectedValue);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system \r\n");

    //get the book information from book ID
    QString bookInfos = c->sendRequest("getBookInfoRequest|",
                                       QString("frank").append("|").append("1"));
    QStringList bookInfo = bookInfos.split("|");
    QString BookID, BookName, BookPrice;
    BookID = bookInfo[0];
    BookName = bookInfo[1];
    BookPrice = bookInfo[2];
    ui->plainTextEdit_3->appendPlainText(QString("BookID : ").append(BookID));
    ui->plainTextEdit_3->appendPlainText(QString("BookName : ").append(BookName));
    ui->plainTextEdit_3->appendPlainText(QString("BookPrice : ").append(BookPrice));
    if(BookID == "1" && BookName == "helloworld" && BookPrice == "10.99")
    {
        ui->plainTextEdit_3->appendPlainText("Test case passed\r\n");
    } else {
        ui->plainTextEdit_3->appendPlainText("Test case failed\r\n");
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank login out the system \r\n\r\n");
}

void MainWindow::on_pushButton_3_clicked()
{
    clearTest();

    QString testDescription = "This test case check the Chapter information from Chapter ID\r\n";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedValue = "ChapterID : 1\r\nChapterName : chapter 1\r\nChapterPrice : 2\r\n";
    ui->plainTextEdit_2->appendPlainText(expectedValue);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system \r\n");

    //get the book information from book ID
    QString chapterInfos = c->sendRequest("getChapterInfoRequest|",
                                       QString("frank").append("|").append("1"));
    QStringList chapterInfo = chapterInfos.split("|");
    QString chapterID, chapterName, chapterPrice;
    chapterID = chapterInfo[0];
    chapterName = chapterInfo[1];
    chapterPrice = chapterInfo[2];
    ui->plainTextEdit_3->appendPlainText(QString("ChapterID : ").append(chapterID));
    ui->plainTextEdit_3->appendPlainText(QString("ChapterName : ").append(chapterName));
    ui->plainTextEdit_3->appendPlainText(QString("ChapterPrice : ").append(chapterPrice));
    if(chapterID == "1" && chapterName == "chapter 1" && chapterPrice == "2")
    {
        ui->plainTextEdit_3->appendPlainText("Test case passed\r\n");
    } else {
        ui->plainTextEdit_3->appendPlainText("Test case failed\r\n");
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank login out the system \r\n\r\n");
}

void MainWindow::on_pushButton_4_clicked()
{
    clearTest();

    QString testDescription = "This test case check the Section information from Section ID\r\n";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedValue = "SectionID : 1\r\nSectionName : section a\r\nSectionPrice : 1\r\n";
    ui->plainTextEdit_2->appendPlainText(expectedValue);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system \r\n");

    //get the book information from book ID
    QString sectionInfos = c->sendRequest("getSectionInfoRequest|",
                                       QString("frank").append("|").append("1"));
    QStringList sectionInfo = sectionInfos.split("|");
    QString sectionID, sectionName, sectionPrice;
    sectionID = sectionInfo[0];
    sectionName = sectionInfo[1];
    sectionPrice = sectionInfo[2];
    ui->plainTextEdit_3->appendPlainText(QString("SectionID : ").append(sectionID));
    ui->plainTextEdit_3->appendPlainText(QString("SectionName : ").append(sectionName));
    ui->plainTextEdit_3->appendPlainText(QString("SectionPrice : ").append(sectionPrice));
    if(sectionID == "1" && sectionName == "section a" && sectionPrice == "1")
    {
        ui->plainTextEdit_3->appendPlainText("Test case passed\r\n");
    } else {
        ui->plainTextEdit_3->appendPlainText("Test case failed\r\n");
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank login out the system \r\n\r\n");
}

void MainWindow::on_pushButton_5_clicked()
{

}

void MainWindow::on_pushButton_6_clicked()
{

}

void MainWindow::on_pushButton_7_clicked()
{

}

void MainWindow::on_pushButton_8_clicked()
{

}

void MainWindow::on_pushButton_9_clicked()
{

}

void MainWindow::on_pushButton_10_clicked()
{

}
