#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QIcon>
#include <QSettings>
#include <QList>

#include "main/include/home.h"
#include "main/include/serverdata.h"

#include "account/include/login.h"
#include "account/include/signup.h"
#include "account/include/accountsettings.h"

#include "contacts/include/contactswindow.h"
#include "contacts/include/entry.h"
#include "contacts/include/deletetags.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    static void SaveCookies(QString UN, QString PW, QString FIRST, QString LAST);
    QList<QString> LoadCookies();
    void ClearCookies();
    static QSqlDatabase SetUpDatabase();

    int id;
    QString sUsername;
    QString sPassword;
    QString sFirst;
    QString sLast;

    void LoginFrame(bool bSignIn);
    void SignUpFrame(bool bLogin);
    void ContactsFrame(); // coming back from adding item
    void AddFrame();
    void EditFrame(int itemID, QJsonObject objContactData);
    void HomeFrame();
    void DeleteTagsFrame(QMap<int, QJsonObject> objAllData);
    void AccountSettingsFrame();

    static void ImageCookie(int id);
    static int LoadImageCookie();
private:
    SignUp *signup = new SignUp();
    Login *login = new Login();
    ContactsWindow *contactsWindow = new ContactsWindow();
    Entry *entry = new Entry();
    DeleteTags *delTags = new DeleteTags();
    Home *homepage = new Home();
    AccountSettings *accountSettings = new AccountSettings();

};
#endif // MAINWINDOW_H
