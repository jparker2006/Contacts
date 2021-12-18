#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QIcon>
#include <QSettings>
#include <QList>

#include "include/login.h"
#include "include/signup.h"
#include "include/contactswindow.h"
#include "include/add.h"
#include "include/serverdata.h"
#include "include/edit.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    static void SaveCookies(QString UN, QString PW);
    QList<QString> LoadCookies();
    void ClearCookies();
    static QSqlDatabase SetUpDatabase();

    void LoginFrame(bool bSignIn);
    void SignUpFrame(bool bLogin);
    void MainFrame(QString un, QString pw);
    void MainFrame(); // coming back from adding item
    void AddFrame(QString un, QString pw, int id);
    void EditFrame(int itemID, QJsonObject objContactData);
private:
    SignUp *signup = new SignUp();
    Login *login = new Login();
    ContactsWindow *main = new ContactsWindow();
    Add *add = new Add();
    Edit *edit = new Edit();
};
#endif // MAINWINDOW_H
