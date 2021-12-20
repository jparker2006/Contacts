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

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB);
    QSqlDatabase db = MainWindow::SetUpDatabase();

    QSqlQuery pull(db);
    pull.prepare("SELECT id, data FROM Contacts WHERE user=:id");
    pull.bindValue(":id", this->id);
    pull.exec();
    while (pull.next()) {
        QJsonDocument jsonContactData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(pull.value(1).toByteArray(), pw.toLocal8Bit())));
        QJsonObject objContactData = jsonContactData.object();
        if (objContactData["first"].toString().isEmpty()) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, pull.value(0).toInt());
            item->setText(objContactData["company"].toString());
            ui->list->addItem(item);
        }
        else {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, pull.value(0).toInt());
            item->setText(objContactData["first"].toString() + " " + objContactData["last"].toString());
            ui->list->addItem(item);
        }
    }

    db.close();
    delete cipher;
}


void ContactsWindow::on_list_itemDoubleClicked(QListWidgetItem *item) {
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT data FROM Contacts WHERE id=:id");
    query.bindValue(":id", item->data(-1).toInt());
    query.exec();
    query.next();

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB);

    QJsonDocument jsonContactData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(query.value(0).toByteArray(), pw.toLocal8Bit())));
    QJsonObject objContactData = jsonContactData.object();
    w->EditFrame(item->data(-1).toInt(), objContactData, this->pw);
}







