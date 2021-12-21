#include "include/edit.h"
#include "include/mainwindow.h"
extern MainWindow *w;

Edit::Edit(QWidget *parent): QMainWindow(parent), ui(new Ui::Edit) {
    ui->setupUi(this);
    setWindowTitle("Editing"); // maybe make this contacts name
}

Edit::~Edit() {
    delete ui;
}

void Edit::passData(int id, QJsonObject objData, QString key) {
    this->nId = id;
    this->objContactData = objData;
    this->key = key;
    setupContactData();
}

void Edit::setupContactData() {
    ui->first->setText(objContactData["first"].toString({""}));
    ui->middle->setText(objContactData["middle"].toString({""}));
    ui->last->setText(objContactData["last"].toString({""}));
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

void Edit::on_b_back_clicked() {
    w->MainFrame();
}

void Edit::on_b_delete_clicked() {
    QMessageBox *confirm = new QMessageBox();
    confirm->setWindowTitle("Deleting Contact"); // make contact name?
    confirm->setText("Are you sure you want to delete this contact forever?");
    confirm->setStandardButtons(QMessageBox::Yes);
    confirm->addButton(QMessageBox::No);
    confirm->setDefaultButton(QMessageBox::No);
    if (QMessageBox::No == confirm->exec())
      return;

    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery deleteQuery(db);
    deleteQuery.prepare("DELETE FROM Contacts WHERE id=:id");
    deleteQuery.bindValue(":id", this->nId);
    deleteQuery.exec();
    db.close();
    w->MainFrame();
}



void Edit::on_add_clicked() {
    QString sFirst = ui->first->text();
    QString sCompany = ui->company->text();

    if (sFirst.isEmpty() && sCompany.isEmpty()) {
        QMessageBox *alert = new QMessageBox();
        alert->setText("Either company or name must be filled out");
        alert->exec();
        return;
    }

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

    QJsonDocument jsonContactData;
    jsonContactData.setObject(objContactData);

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QByteArray encodedText = cipher->encode(jsonContactData.toJson(), this->key.toLocal8Bit());

    QSqlDatabase db = MainWindow::SetUpDatabase();

    QSqlQuery query(db);
    query.prepare("UPDATE Contacts SET data=:data WHERE id=:id");
    query.bindValue(":id", this->nId);
    query.bindValue(":data", encodedText);
    query.exec();

    db.close();
    w->MainFrame();
}

