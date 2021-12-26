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
#include "include/serverdata.h"
#include "include/entry.h"
#include "include/deletetags.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    static void SaveCookies(QString UN, QString PW);
    QList<QString> LoadCookies();
    void ClearCookies();
    static QSqlDatabase SetUpDatabase();
    int id;

    void LoginFrame(bool bSignIn);
    void SignUpFrame(bool bLogin);
    void MainFrame(QString un, QString pw);
    void MainFrame(); // coming back from adding item
    void AddFrame(QString un, QString pw, int id);
    void EditFrame(int itemID, QJsonObject objContactData, QString pw, int nUserID);
    void HomeFrame();
    void DeleteTagsFrame(int id, QString sKey, QMap<int, QJsonObject> objAllData);
private:
    SignUp *signup = new SignUp();
    Login *login = new Login();
    ContactsWindow *main = new ContactsWindow();
    Entry *entry = new Entry();
    DeleteTags *delTags = new DeleteTags();

};
#endif // MAINWINDOW_H
