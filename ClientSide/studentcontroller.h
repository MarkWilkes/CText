#ifndef STUDENTCONTROLLER_H
#define STUDENTCONTROLLER_H

#include <ui_loginPage.h>
#include <QMainWindow>
#include <QObject>
#include <QMessageBox>
#include "clientconnection.h"
#include "../Common/course.h"
#include "../Common/cart.h"

namespace Ui {
class MainWindow;
}

class StudentController : public QObject
{
    Q_OBJECT
public:
    explicit StudentController(QObject *parent = 0,
                               ClientConnection *c = 0,
                               Ui::MainWindow *ui = 0);
    void initialize(QString studentID);

signals:
    void sendMsg(QString, QString);

private slots:
    void viewCourseButtonClicked();
    void addCartButtonClicked();
    void shoppingCartButtonClicked();
    void placeOrderButtonClicked();
    void cancelOrderButtonClicked();
    void studentViewListChanged();
private:
    ClientConnection *c;
    Ui::MainWindow *ui;
    QList<Course*> courses;
    QString studentID;

    //function for the QTreeWidget
    QTreeWidgetItem* addRoot(QString name, QString price);
    QTreeWidgetItem *addChild(QTreeWidgetItem *parent, QString name, QString price);
};

#endif // STUDENTCONTROLLER_H
