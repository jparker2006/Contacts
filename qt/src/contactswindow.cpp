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
    QVector<QMap<int, QJsonObject>*> *objAllContactData = new QVector<QMap<int, QJsonObject>*>;
    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();

    QSqlQuery pull(db);
    pull.prepare("SELECT id, data FROM Contacts WHERE user=:id");
    pull.bindValue(":id", this->id);
    pull.exec();
    while (pull.next()) {
        QJsonDocument jsonContactData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(pull.value(1).toByteArray(), pw.toUtf8())));
        QJsonObject objContactData = jsonContactData.object();
        QMap<int, QJsonObject> *curr = new QMap<int, QJsonObject>;
        curr->insert(pull.value(0).toInt(), objContactData);
        objAllContactData->push_back(curr);

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
    for (int i=0; i<objAllContactData->length(); i++) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(-1, objAllContactData->at(i)->begin().key());
        QJsonObject jsonCurrent = objAllContactData->at(i)->begin().value();
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
    for (int i=0; i<objAllContactData->length(); i++) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(-1, objAllContactData->at(i)->begin().key());
        QJsonObject jsonCurrent = objAllContactData->at(i)->begin().value();
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
    for (int x=0; x<this->objAllContactData->length(); x++) {
        int nCurrId = objAllContactData->at(x)->begin().key();
        QJsonObject objCurr = objAllContactData->at(x)->begin().value();
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
    if (objData["first"].toString().contains(sAjax))       return true;
    if (objData["middle"].toString().contains(sAjax))      return true;
    if (objData["last"].toString().contains(sAjax))        return true;
    if (objData["company"].toString().contains(sAjax))     return true;
    if (objData["title"].toString().contains(sAjax))       return true;
    if (objData["home"].toString().contains(sAjax))        return true;
    if (objData["mobile"].toString().contains(sAjax))      return true;
    if (objData["work"].toString().contains(sAjax))        return true;
    if (objData["adress"].toString().contains(sAjax))      return true;
    if (objData["email"].toString().contains(sAjax))       return true;
    if (objData["website"].toString().contains(sAjax))     return true;
    if (objData["state"].toString().contains(sAjax))       return true;
    if (objData["city"].toString().contains(sAjax))        return true;
    if (objData["zip"].toString().contains(sAjax))         return true;
    if (objData["birthday"].toString().contains(sAjax))    return true;
    if (objData["anniversary"].toString().contains(sAjax)) return true;
    if (objData["notes"].toString().contains(sAjax))       return true;
    return false;
}

void ContactsWindow::clearAjaxBox() {
    ui->ajax->clear();
}
