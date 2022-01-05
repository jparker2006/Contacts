#include "main/include/mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    QList<QString> cookies = LoadCookies();
    if (cookies.size() != 2) {
        SignUpFrame(false);
        return;
    }

    this->sUsername = cookies[0];
    this->sPassword = cookies[1];
    QSqlDatabase db = SetUpDatabase();

    QSqlQuery query(db);
    query.prepare("SELECT id FROM Users WHERE username=:username");
    query.bindValue(":username", this->sUsername);
    query.exec();
    query.next();
    this->id = query.value(0).toInt();
    query.clear();
    query.prepare("UPDATE Users SET lastlogin=CURRENT_TIMESTAMP WHERE username=:username");
    query.bindValue(":username", this->sUsername);
    query.exec();
    db.close();
    HomeFrame();
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

void MainWindow::ContactsFrame() {
    QList<QString> cookies = LoadCookies(); // coming from login this is neeeded
    this->sUsername = cookies[0];
    this->sPassword = cookies[1];

    if (login->isEnabled())
        login->hide();
    if (signup->isEnabled())
        signup->hide();
    if (homepage->isEnabled()) {
        homepage->hide();
    }
    if (homepage->isEnabled()) {
        homepage->hide();
    }
    if (entry->isEnabled()) {
        entry->hide();
    }
    if (delTags->isEnabled()) {
        delTags->hide();
    }

    main->clearAjaxBox();
    main->pullData();
    main->show();
}

void MainWindow::AddFrame() {
    main->hide();
    entry->a_passData(); // really just a_setup
    entry->setUpTags();
    entry->show();
}

void MainWindow::EditFrame(int itemID, QJsonObject objContactData) {
    main->hide();
    entry->setUpTags();
    entry->e_passData(objContactData, itemID);

    entry->show();
}

void MainWindow::DeleteTagsFrame(QMap<int, QJsonObject> objAllData) {
    main->hide();
    delTags->passData(objAllData);
    delTags->show();
}

void MainWindow::HomeFrame() {
    main->hide(); // main is contacts window main
    homepage->show();
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
    db.setDatabaseName("Contacts");
    db.setUserName("jake_contacts");
    db.setHostName(IP);
    db.setPort(PORT);
    db.setPassword(DB_PASSWORD);
    if (!db.open()) {
        QMessageBox alert;
        alert.setText("Database not operating");
        alert.exec();
        exit(69);
    }
    return db;
}

