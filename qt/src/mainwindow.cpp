#include "include/mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    QList<QString> cookies = LoadCookies();
    if (cookies.size() != 2)
        SignUpFrame(false);
    else
        MainFrame(cookies[0], cookies[1]);
}

void MainWindow::LoginFrame(bool bSignIn) { // true ? delete sign in : none
    if (bSignIn)
        signup->hide();

    login->show();
}

void MainWindow::SignUpFrame(bool bLogin) {
    if (bLogin)
        login->hide();

    signup->show();
}

void MainWindow::MainFrame(QString un, QString pw) {
    main->passUserData(un, pw);

    if (login->isEnabled())
        login->hide();
    else if (signup->isEnabled())
        signup->hide();

    main->show();
}

void MainWindow::SaveCookies(QString UN, QString PW) { static
    QSettings cookies("Contacts", "cookies");
    cookies.beginGroup("CookiesGroup");
    cookies.setValue("UN", UN);
    cookies.setValue("PW", PW);
    cookies.endGroup();
}

QList<QString> MainWindow::LoadCookies() {
    QSettings cookies("Contacts", "cookies");
    cookies.beginGroup("CookiesGroup");
    QString un = cookies.value("UN").toString();
    QString pw = cookies.value("PW").toString();
    cookies.endGroup();

    if (un.isEmpty() || pw.isEmpty())
        return QList<QString> {"no cookies"};
    else
        return QList<QString> {un, pw};
}

void MainWindow::ClearCookies() { // just for testing purposes
    QSettings cookies("Contacts", "cookies");
    cookies.beginGroup("CookiesGroup");
    cookies.setValue("UN", "");
    cookies.setValue("PW", "");
    cookies.endGroup();
}

