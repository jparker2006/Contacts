#include "main/include/mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    QList<QString> cookies = LoadCookies();
    if (1 == cookies.size()) {
        SignUpFrame(false);
        return;
    }

    this->sUsername = cookies[0];
    this->sPassword = cookies[1];
    this->sFirst = cookies[2];
    this->sLast = cookies[3];
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

    contactsWindow->clearAjaxBox();
    contactsWindow->pullData();
    contactsWindow->show();
}

void MainWindow::AddFrame() {
    contactsWindow->hide();
    entry->a_passData(); // really just a_setup
    entry->setUpTags();
    entry->show();
}

void MainWindow::EditFrame(int itemID, QJsonObject objContactData) {
    contactsWindow->hide();
    entry->setUpTags();
    entry->e_passData(objContactData, itemID);

    entry->show();
}

void MainWindow::DeleteTagsFrame(QMap<int, QJsonObject> objAllData) {
    contactsWindow->hide();
    delTags->passData(objAllData);
    delTags->show();
}

void MainWindow::AccountSettingsFrame() {
    homepage->hide();
    accountSettings->show();
    accountSettings->setupData();
}

void MainWindow::HomeFrame() {
    QList<QString> cookies = LoadCookies();
    this->sUsername = cookies[0];
    this->sPassword = cookies[1];
    this->sFirst = cookies[2];
    this->sLast = cookies[3];

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

    login->hide();
    signup->hide();
    contactsWindow->hide();
    accountSettings->hide();

    homepage->show();
    if (MainWindow::LoadImageCookie() != 0)
        homepage->setupPFP(this->sPassword);
}

void MainWindow::SaveCookies(QString UN, QString PW, QString FIRST, QString LAST) { static
    QSettings cookies("Contacts", "cookies");
    cookies.beginGroup("CookiesGroup");
    cookies.setValue("UN", UN);
    cookies.setValue("PW", PW);
    cookies.setValue("FIRST", FIRST);
    cookies.setValue("LAST", LAST);
    cookies.endGroup();
}

QList<QString> MainWindow::LoadCookies() {
    QSettings cookies("Contacts", "cookies");
    cookies.beginGroup("CookiesGroup");
    QString un = cookies.value("UN").toString();
    QString pw = cookies.value("PW").toString();
    QString first = cookies.value("FIRST").toString();
    QString last = cookies.value("LAST").toString();
    cookies.endGroup();

    if (un.isEmpty() || pw.isEmpty())
        return QList<QString> {"no cookies"};
    else
        return QList<QString> {un, pw, first, last};
}

void MainWindow::ClearCookies() {
    QSettings cookies("Contacts", "cookies");
    cookies.beginGroup("CookiesGroup");
    cookies.setValue("UN", "");
    cookies.setValue("PW", "");
    cookies.endGroup();
}

void MainWindow::ImageCookie(int id) { static
    QSettings cookies("Images", "imageCookie");
    cookies.beginGroup("ImageCookie");
    cookies.setValue("Id", id);
    cookies.endGroup();
}

int MainWindow::LoadImageCookie() { static
    QSettings cookies("Images", "imageCookie");
    cookies.beginGroup("ImageCookie");
    int imgID = cookies.value("Id").toInt();
    cookies.endGroup();

    return imgID;
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

