#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QIcon>
#include <QSettings>
#include <QList>
#include <QClipboard>
#include <QMessageBox>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPushButton>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QInputDialog>
#include <QMouseEvent>
#include <QVector>
#include <QRandomGenerator>

#include "main/include/home.h"
#include "main/include/serverdata.h"
#include "main/crypto/qaesencryption.h"
#include "main/crypto/sha3.h"

#include "account/include/login.h"
#include "account/include/signup.h"
#include "account/include/accountsettings.h"

#include "contacts/include/contactswindow.h"
#include "contacts/include/entry.h"
#include "contacts/include/deletetags.h"

#include "pwmanager/include/passwordwindow.h"
#include "pwmanager/include/pw_entry.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    static void SaveCookies(QString UN, QString PW, QString FIRST, QString LAST);
    QList<QString> LoadCookies();
    static void ClearCookies();
    static QSqlDatabase SetUpDatabase();

    int id;
    QString sUsername;
    QString sPassword;
    QString sFirst;
    QString sLast;

    void LoginFrame();
    void SignUpFrame();

    void ContactsFrame();
    void AddFrame();
    void EditFrame(int itemID, QJsonObject objContactData);
    void HomeFrame();
    void DeleteTagsFrame(QMap<int, QJsonObject> objAllData);

    void AccountSettingsFrame();

    void PasswordFrame();
    void PW_AddFrame();

    void HideAllFrames();

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
    PasswordWindow *passwordWindow = new PasswordWindow();
    pw_entry *pass_entry = new pw_entry();

};
#endif // MAINWINDOW_H
