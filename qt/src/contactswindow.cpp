#include "include/contactswindow.h"
#include "include/mainwindow.h"

extern MainWindow *w;

ContactsWindow::ContactsWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::ContactsWindow) {
    ui->setupUi(this);
    setWindowTitle("Contacts");
}

ContactsWindow::~ContactsWindow() {
    delete ui;
}

void ContactsWindow::passUserData(QString un, QString pw, int id) {
    this->un = un;
    this->pw = pw;
    this->id = id;
}

void ContactsWindow::on_add_clicked() {
    w->AddFrame(un, pw, id);
}

void ContactsWindow::pullData() {
    ui->list->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.112");
    db.setDatabaseName("Contacts");
    db.setUserName("jake_contacts");
    db.setPassword("Yv9zEtKfr5yMPgkvWa4v9N");
    db.open();

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB);

    QSqlQuery pull(db);
    pull.prepare("SELECT data FROM Contacts WHERE user=:id");
    pull.bindValue(":id", this->id);
    pull.exec();
    while (pull.next()) {
        QJsonDocument jsonContactData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(pull.value(0).toByteArray(), pw.toLocal8Bit())));
        QJsonObject objContactData = jsonContactData.object();
        if (objContactData["first"].toString().isEmpty())
            ui->list->addItem(objContactData["company"].toString());
        else
            ui->list->addItem(objContactData["first"].toString() + " " + objContactData["last"].toString());
    }

    db.close();
    delete cipher;
}








