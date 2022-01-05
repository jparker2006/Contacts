#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QIcon>
#include <QSettings>
#include <QList>

#include "account/include/login.h"
#include "account/include/signup.h"
#include "contacts/include/contactswindow.h"
#include "main/include/serverdata.h"
#include "contacts/include/entry.h"
#include "contacts/include/deletetags.h"
#include "main/include/home.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    static void SaveCookies(QString UN, QString PW);
    QList<QString> LoadCookies();
    void ClearCookies();
    static QSqlDatabase SetUpDatabase();

    int id;
    QString sUsername;
    QString sPassword;

    void LoginFrame(bool bSignIn);
    void SignUpFrame(bool bLogin);
    void ContactsFrame(); // coming back from adding item
    void AddFrame();
    void EditFrame(int itemID, QJsonObject objContactData);
    void HomeFrame();
    void DeleteTagsFrame(QMap<int, QJsonObject> objAllData);

    Home *homepage = new Home();
private:


    SignUp *signup = new SignUp();
    Login *login = new Login();
    ContactsWindow *main = new ContactsWindow();
    Entry *entry = new Entry();
    DeleteTags *delTags = new DeleteTags();


};
#endif // MAINWINDOW_H
