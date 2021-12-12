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

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void LoginFrame(bool bSignIn);
    void SignUpFrame(bool bLogin);
    void MainFrame(QString un, QString pw);
    static void SaveCookies(QString UN, QString PW);
    QList<QString> LoadCookies();
    void ClearCookies();
private:
    SignUp *signup = new SignUp();
    Login *login = new Login();
    ContactsWindow *main = new ContactsWindow();
};
#endif // MAINWINDOW_H
