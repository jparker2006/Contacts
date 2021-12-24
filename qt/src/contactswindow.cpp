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

void ContactsWindow::pullData() { // needs a refactor
    ui->list->clear();
    QMap<int, QJsonObject> objAllContactData = {};
    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();

    QSqlQuery pull(db);
    pull.prepare("SELECT id, data FROM Contacts WHERE user=:id");
    pull.bindValue(":id", this->id);
    pull.exec();

    while (pull.next()) {
        QJsonDocument jsonContactData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(pull.value(1).toByteArray(), pw.toUtf8())));
        QJsonObject objContactData = jsonContactData.object();
        objAllContactData.insert(pull.value(0).toInt(), objContactData);

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
    this->objAllContactData = objAllContactData;
}

void ContactsWindow::on_list_itemDoubleClicked(QListWidgetItem *item) {
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT data FROM Contacts WHERE id=:id");
    query.bindValue(":id", item->data(-1).toInt());
    query.exec();
    query.next();

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);

    QJsonDocument jsonContactData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(query.value(0).toByteArray(), pw.toUtf8())));
    QJsonObject objContactData = jsonContactData.object();

    w->EditFrame(item->data(-1).toInt(), objContactData, this->pw);
}

void ContactsWindow::on_s_first_clicked() {
    ui->list->clear();
    QMapIterator<int, QJsonObject> iter(objAllContactData);
    while (iter.hasNext()) {
        iter.next();

        QListWidgetItem *item = new QListWidgetItem();
        item->setData(-1, iter.key());
        QJsonObject jsonCurrent = iter.value();

        if (jsonCurrent["first"].toString().isEmpty())
            item->setText(jsonCurrent["company"].toString());
        else
            item->setText(jsonCurrent["first"].toString() + " " + jsonCurrent["last"].toString());
        ui->list->addItem(item);
    }
    ui->list->sortItems();
}

void ContactsWindow::on_s_last_clicked() {
    ui->list->clear();

    QMapIterator<int, QJsonObject> iter(objAllContactData);
    while (iter.hasNext()) {
        iter.next();

        QListWidgetItem *item = new QListWidgetItem();

        item->setData(-1, iter.key());
        QJsonObject jsonCurrent = iter.value();

        if (jsonCurrent["first"].toString().isEmpty())
            item->setText(jsonCurrent["company"].toString());
        else {
            if (jsonCurrent["last"].toString().isEmpty())
                item->setText(jsonCurrent["first"].toString());
            else
                item->setText(jsonCurrent["last"].toString() + ", " + jsonCurrent["first"].toString());
        }
        ui->list->addItem(item);
    }

    ui->list->sortItems();
}

void ContactsWindow::on_ajax_textChanged(const QString &sAjax) {
    ui->list->clear();
    QMapIterator<int, QJsonObject> iter(objAllContactData);
    while (iter.hasNext()) {
        iter.next();

        int nCurrId = iter.key();
        QJsonObject objCurr = iter.value();

        if (partOfJsonInAjax(objCurr, sAjax)) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, nCurrId);
            if (objCurr["first"].toString().isEmpty())
                item->setText(objCurr["company"].toString());
            else
                item->setText(objCurr["first"].toString() + " " + objCurr["last"].toString());
            ui->list->addItem(item);
        }
    }
}

bool ContactsWindow::partOfJsonInAjax(QJsonObject objData, QString sAjax) {
    if (objData["first"].toString().toLower().contains(sAjax.toLower()))       return true;
    if (objData["middle"].toString().toLower().contains(sAjax.toLower()))      return true;
    if (objData["last"].toString().toLower().contains(sAjax.toLower()))        return true;
    if (objData["company"].toString().toLower().contains(sAjax.toLower()))     return true;
    if (objData["title"].toString().toLower().contains(sAjax.toLower()))       return true;
    if (objData["home"].toString().toLower().contains(sAjax.toLower()))        return true;
    if (objData["mobile"].toString().toLower().contains(sAjax.toLower()))      return true;
    if (objData["work"].toString().toLower().contains(sAjax.toLower()))        return true;
    if (objData["address"].toString().toLower().contains(sAjax.toLower()))     return true;
    if (objData["email"].toString().toLower().contains(sAjax.toLower()))       return true;
    if (objData["website"].toString().toLower().contains(sAjax.toLower()))     return true;
    if (objData["state"].toString().toLower().contains(sAjax.toLower()))       return true;
    if (objData["city"].toString().toLower().contains(sAjax.toLower()))        return true;
    if (objData["zip"].toString().toLower().contains(sAjax.toLower()))         return true;
    if (objData["birthday"].toString().toLower().contains(sAjax.toLower()))    return true;
    if (objData["anniversary"].toString().toLower().contains(sAjax.toLower())) return true;
    if (objData["notes"].toString().toLower().contains(sAjax.toLower()))       return true;
    return false;
}

void ContactsWindow::clearAjaxBox() {
    ui->ajax->clear();
}
