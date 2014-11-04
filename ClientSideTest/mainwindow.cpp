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
    QString expectedValue = QString("CourseID : COMP3004 \r\nCourseName : Object-Oriented Software Engineer\r\n")
            .append("CourseID : COMP3000 \r\nCourseName : Operating Systems");
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
            if(courseID == "COMP3000" && courseName == "Operating Systems")
            {
                ui->plainTextEdit_3->appendPlainText("Test case passed\r\n");
            } else {
                ui->plainTextEdit_3->appendPlainText("Test case failed\r\n");
            }
        }
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank logout the system \r\n\r\n");
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
    ui->plainTextEdit_3->appendPlainText("frank logut the system \r\n\r\n");
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
    ui->plainTextEdit_3->appendPlainText("frank logout the system \r\n\r\n");
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
    ui->plainTextEdit_3->appendPlainText("frank logout the system \r\n\r\n");
}

void MainWindow::on_pushButton_5_clicked()
{
    clearTest();
    QString testDescription = "This test case checks the CartID from the StudentID";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedResult = "The expected result is '1'";
    ui->plainTextEdit_2->appendPlainText(expectedResult);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system \r\n");

    //get cartID from system
    QString cartID = c->sendRequest("getCartID|","frank");
    ui->plainTextEdit_3->appendPlainText("CartID: " + cartID);
    if(cartID.compare("1") == 0){
        ui->plainTextEdit_3->appendPlainText("\nTest Passed");
    }
    else{
        ui->plainTextEdit_3->appendPlainText("\nTest Failed");
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank logut the system \r\n\r\n");
}

void MainWindow::on_pushButton_6_clicked()
{
    clearTest();
    QString testDescription = "This test case checks the CartInfo from the CartID";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedResult = "The expected result is '1','1','2,3','1'";
    ui->plainTextEdit_2->appendPlainText(expectedResult);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system \r\n");

    //get cartID from system
    QString cartID = c->sendRequest("getCartID|","frank");

    //get cartFromID from system

    QString cart = c->sendRequest("getCartInfoRequest|","frank|"+cartID);

    QStringList cartList = cart.split("|");

    ui->plainTextEdit_3->appendPlainText("CartID:"+cartList.at(0) + "\n");
    ui->plainTextEdit_3->appendPlainText("CartBooks"+cartList.at(1)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartChapters"+cartList.at(2)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartSections"+cartList.at(3)+"\n");

    if(cartList[0].compare("1")==0
       &&cartList[1].compare("1")==0
       &&cartList[2].compare("2,3")==0
       &&cartList[3].compare("1")==0){
        ui->plainTextEdit_3->appendPlainText("\nTest Passed");
    }
    else{
        ui->plainTextEdit_3->appendPlainText("\nTest Failed");
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank logut the system \r\n\r\n");
}

void MainWindow::on_pushButton_7_clicked()
{
    clearTest();
    QString testDescription = "This test case empties the cart";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedResult = "The expected result is '1','','',''";
    ui->plainTextEdit_2->appendPlainText(expectedResult);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system \r\n");

    //get cartID from system
    QString cartID = c->sendRequest("getCartID|","frank");

    //get cartFromID from system

    QString cart = c->sendRequest("getCartInfoRequest|","frank|"+cartID);

    QStringList cartList = cart.split("|");
    ui->plainTextEdit_3->appendPlainText("Before empty\r\n");
    ui->plainTextEdit_3->appendPlainText("CartID: "+cartList.at(0) + "\n");
    ui->plainTextEdit_3->appendPlainText("CartBooks: "+cartList.at(1)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartChapters: "+cartList.at(2)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartSections: "+cartList.at(3)+"\n");

    c->sendRequest("setCart|","1|||");

    cart = c->sendRequest("getCartInfoRequest|","frank|"+cartID);

    cartList = cart.split("|");
    ui->plainTextEdit_3->appendPlainText("After empty\r\n");
    ui->plainTextEdit_3->appendPlainText("CartID: "+cartList.at(0) + "\n");
    ui->plainTextEdit_3->appendPlainText("CartBooks: "+cartList.at(1)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartChapters: "+cartList.at(2)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartSections: "+cartList.at(3)+"\n");

    if(cartList[0].compare("1") == 0
       &&cartList[1].isEmpty()
       &&cartList[2].isEmpty()
       &&cartList[3].isEmpty()){
        ui->plainTextEdit_3->appendPlainText("\nTest Passed");
    }
    else{
        ui->plainTextEdit_3->appendPlainText("\nTest Failed");
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank logut the system \r\n\r\n");
}

void MainWindow::on_pushButton_8_clicked()
{
    clearTest();
    QString testDescription = "This test case fills the cart";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedResult = "The expected result is '1','1','2,3','1'";
    ui->plainTextEdit_2->appendPlainText(expectedResult);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system \r\n");

    //get cartID from system
    QString cartID = c->sendRequest("getCartID|","frank");

    //get cartFromID from system

    QString cart = c->sendRequest("getCartInfoRequest|","frank|"+cartID);

    QStringList cartList = cart.split("|");
    ui->plainTextEdit_3->appendPlainText("Before fill\r\n");
    ui->plainTextEdit_3->appendPlainText("CartID: "+cartList.at(0) + "\n");
    ui->plainTextEdit_3->appendPlainText("CartBooks: "+cartList.at(1)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartChapters: "+cartList.at(2)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartSections: "+cartList.at(3)+"\n");

    c->sendRequest("setCart|","1|1|2,3|1");

    cart = c->sendRequest("getCartInfoRequest|","frank|"+cartID);

    cartList = cart.split("|");
    ui->plainTextEdit_3->appendPlainText("After Fill\r\n");
    ui->plainTextEdit_3->appendPlainText("CartID: "+cartList.at(0) + "\n");
    ui->plainTextEdit_3->appendPlainText("CartBooks: "+cartList.at(1)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartChapters: "+cartList.at(2)+"\n");
    ui->plainTextEdit_3->appendPlainText("CartSections: "+cartList.at(3)+"\n");

    if(cartList[0].compare("1") == 0
            &&cartList[1].compare("1")==0
            &&cartList[2].compare("2,3")==0
            &&cartList[3].compare("1")==0){
        ui->plainTextEdit_3->appendPlainText("\nTest Passed");
    }
    else{
        ui->plainTextEdit_3->appendPlainText("\nTest Failed");
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank logut the system \r\n\r\n");
}

void MainWindow::on_pushButton_9_clicked()
{
    clearTest();

    QString testDescription = "This test case check the login function of the system, login as 'frank'\r\n";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedValue = QString("Success message for login, and the role for user");
    ui->plainTextEdit_2->appendPlainText(expectedValue);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system");
    if(role == "Student")
    {
        ui->plainTextEdit_3->appendPlainText("Test case passed\r\n");
    } else {
        ui->plainTextEdit_3->appendPlainText("Test case failed\r\n");
    }

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank logout the system \r\n\r\n");
}

void MainWindow::on_pushButton_10_clicked()
{
    clearTest();

    QString testDescription = "This test case check the logout function of the system\r\n";
    ui->plainTextEdit->appendPlainText(testDescription);
    QString expectedValue = QString("Success message for logout");
    ui->plainTextEdit_2->appendPlainText(expectedValue);

    //login the system as frank
    QString role = c->sendRequest("loginRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText(role + " frank login to the system \r\n");

    //logout the system
    role = c->sendRequest("logoutRequest|", "frank");
    ui->plainTextEdit_3->appendPlainText("frank logout the system");
    if(role == "true")
    {
        ui->plainTextEdit_3->appendPlainText("Test case passed\r\n");
    } else {
        ui->plainTextEdit_3->appendPlainText("Test case failed\r\n");
    }
}
