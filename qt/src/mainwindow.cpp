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
    QSqlDatabase db = SetUpDatabase();

    QSqlQuery query(db);
    query.prepare("SELECT id FROM Users WHERE username=:username");
    query.bindValue(":username", un);
    query.exec();
    query.next();
    main->passUserData(un, pw, query.value(0).toInt());
    db.close();

    if (login->isEnabled())
        login->hide();
    else if (signup->isEnabled())
        signup->hide();

    main->show();
    main->pullData();
}

void MainWindow::MainFrame() {
    if (add->isEnabled())
        add->hide();
    if (edit->isEnabled())
        edit->hide();
    main->show();
    main->pullData();
}

void MainWindow::AddFrame(QString un, QString pw, int id) {
    main->hide();
    add->passUserData(un, pw, id);
    add->show();
}

void MainWindow::EditFrame(int itemID, QJsonObject objContactData, QString pw) {
    main->hide();
    edit->passData(itemID, objContactData, pw);
    edit->show();
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

QSqlDatabase MainWindow::SetUpDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //db.setHostName(IP);
    db.setHostName("192.168.1.112");
    //db.setPort(PORT);
    db.setDatabaseName("Contacts");
    db.setUserName("jake_contacts");
    db.setPassword(DB_PASSWORD);
    db.open();
    return db;
}

