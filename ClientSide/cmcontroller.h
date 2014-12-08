#ifndef CMCONTROLLER_H
#define CMCONTROLLER_H

#include <ui_loginPage.h>
#include <QMainWindow>
#include <QObject>
#include "clientconnection.h"
#include "../Common/course.h"

namespace Ui {
class MainWindow;
}

class CmController : public QObject
{
    Q_OBJECT
public:
    explicit CmController(QObject *parent = 0,
                               ClientConnection *c = 0,
                               Ui::MainWindow *ui = 0);

    void initialize(QString userID);

signals:
    void sendMsg(QString, QString);

private slots:
    //main window
    void viewContentButtonClicked();
    void addContentButtonClicked();
    void editContentButtonClicked();
    void viewCourseButtonClicked();
    void addCourseButtonClicked();
    void editCourseButtonClicked();

    void CMViewListChanged();
    void CMCourseListChanged();

    //add content
    void submitButtonClicked();
    void cancelButtonClicked();

    //edit content
    void editSubmitButtonClicked();
    void editCancelButtonClicked();
    void editDeleteButtonClicked();

    //add course
    void addCourseSubmitButtonClicked();
    void addCourseCancelButtonClicked();

    //edit course
    void editCourseSubmitButtonClicked();
    void editCourseDeleteButtonClicked();
    void editCourseCancelButtonClicked();

private:
    ClientConnection *c;
    Ui::MainWindow *ui;
    QString userID;

    //function for the QTreeWidget
    QTreeWidgetItem* addCourse(QString courseID, QString courseName);
    QTreeWidgetItem* addRoot(QString ID, QString name, QString price);
    QTreeWidgetItem *addChild(QTreeWidgetItem *parent, QString ID, QString name, QString price);
};



#endif // CMCONTROLLER_H
