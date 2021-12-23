#include "include/entry.h"
#include "include/mainwindow.h"
extern MainWindow *w;

Entry::Entry(QWidget *parent): QMainWindow(parent), ui(new Ui::Entry) {
    ui->setupUi(this);
    setWindowTitle("Add/Edit Data"); // make this not shitty

    connect(ui->del, &QPushButton::clicked, this, &Entry::e_deleteData);
    connect(ui->add, &QPushButton::clicked, this, &Entry::enterData);
    connect(ui->back, &QPushButton::clicked, this, &Entry::back_clicked);
}

Entry::~Entry() {
    delete ui;
}

void Entry::a_passData(QString sUn, QString sKey, int nId) {
    this->sUn = sUn;
    this->sKey = sKey;
    this->nUserId = nId;
    this->bAdding = true;
    ui->del->hide();
}


void Entry::e_passData(QJsonObject objContactData, QString sKey, int nId) {
    this->objContactData = objContactData;
    this->sKey = sKey;
    this->nItemId = nId;
    this->bAdding = false;
    ui->del->show();
    e_setupData();
}

void Entry::e_setupData() {
    ui->first->setText(objContactData["first"].toString({""}));
    ui->middle->setText(objContactData["middle"].toString({""}));
    ui->last->setText(objContactData["last"].toString({""}));
    ui->company->setText(objContactData["company"].toString({""}));
    ui->title->setText(objContactData["title"].toString({""}));
    ui->home->setText(objContactData["home"].toString({""}));
    ui->mobile->setText(objContactData["mobile"].toString({""}));
    ui->work->setText(objContactData["work"].toString({""}));
    ui->adress->setText(objContactData["adress"].toString({""}));
    ui->email->setText(objContactData["email"].toString({""}));
    ui->website->setText(objContactData["website"].toString({""}));
    ui->state->setText(objContactData["state"].toString({""}));
    ui->city->setText(objContactData["city"].toString({""}));
    ui->zip->setText(objContactData["zip"].toString({""}));
    ui->birthday->setText(objContactData["birthday"].toString({""}));
    ui->anniversary->setText(objContactData["anniversary"].toString({""}));
    ui->notes->setText(objContactData["notes"].toString({""}));
}

void Entry::enterData() {
    QString sFirst = ui->first->text();
    QString sCompany = ui->company->text();

    if (sFirst.isEmpty() && sCompany.isEmpty()) {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Either company or name must be filled out");
        alert->exec();
        return;
    }

    QJsonObject objContactData = fetchJsonData(sFirst, sCompany);
    QJsonDocument *jsonContactData = new QJsonDocument();
    jsonContactData->setObject(objContactData);

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QByteArray ba_jsonContact = cipher->encode(jsonContactData->toJson(QJsonDocument::Compact), sKey.toUtf8());

    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);

    if (bAdding) {
        query.prepare("INSERT INTO Contacts (user, data) VALUES (:user, :data)");
        query.bindValue(":user", this->nUserId);
        query.bindValue(":data", ba_jsonContact);
    }
    else {
        query.prepare("UPDATE Contacts SET data=:data WHERE id=:id");
        query.bindValue(":id", this->nItemId);
        query.bindValue(":data", ba_jsonContact);
    }

    query.exec();
    db.close();
    w->MainFrame();
    clearTextboxes();
}

void Entry::back_clicked() {
    w->MainFrame();
    clearTextboxes();
}

void Entry::e_deleteData() {
    QMessageBox *confirm = new QMessageBox();
    confirm->setWindowTitle("Deleting Contact"); // make contact name
    confirm->setText("Are you sure you want to delete this contact forever?");
    confirm->setStandardButtons(QMessageBox::Yes);
    confirm->addButton(QMessageBox::No);
    confirm->setDefaultButton(QMessageBox::No);
    if (QMessageBox::No == confirm->exec())
      return;

    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery deleteQuery(db);
    deleteQuery.prepare("DELETE FROM Contacts WHERE id=:id");
    deleteQuery.bindValue(":id", this->nItemId);
    deleteQuery.exec();
    db.close();
    w->MainFrame();
    clearTextboxes();
}

void Entry::clearTextboxes() {
    ui->first->setText("");
    ui->company->setText("");
    ui->middle->setText("");
    ui->last->setText("");
    ui->title->setText("");
    ui->home->setText("");
    ui->mobile->setText("");
    ui->work->setText("");
    ui->adress->setText("");
    ui->email->setText("");
    ui->website->setText("");
    ui->state->setText("");
    ui->city->setText("");
    ui->zip->setText("");
    ui->birthday->setText("");
    ui->anniversary->setText("");
    ui->notes->setText("");
}

QJsonObject Entry::fetchJsonData(QString sFirst, QString sCompany) {
    QJsonObject objContactData;
    objContactData["first"] = sFirst;
    objContactData["company"] = sCompany;
    objContactData["middle"] = ui->middle->text();
    objContactData["last"] = ui->last->text();
    objContactData["title"] = ui->title->text();
    objContactData["home"] = ui->home->text();
    objContactData["mobile"] = ui->mobile->text();
    objContactData["work"] = ui->work->text();
    objContactData["adress"] = ui->adress->text();
    objContactData["email"] = ui->email->text();
    objContactData["website"] = ui->website->text();
    objContactData["state"] = ui->state->text();
    objContactData["city"] = ui->city->text();
    objContactData["zip"] = ui->zip->text();
    objContactData["birthday"] = ui->birthday->text();
    objContactData["anniversary"] = ui->anniversary->text();
    objContactData["notes"] = ui->notes->text();
    return objContactData;
}
