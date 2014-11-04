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
    void viewContentButtonClicked();
    void addContentButtonClicked();
    void editContentButtonClicked();

    void submitButtonClicked();
    void cancelButtonClicked();

private:
    ClientConnection *c;
    Ui::MainWindow *ui;
    QString userID;

    //function for the QTreeWidget
    QTreeWidgetItem* addRoot(QString name, QString price);
    QTreeWidgetItem *addChild(QTreeWidgetItem *parent, QString name, QString price);
};



#endif // CMCONTROLLER_H
