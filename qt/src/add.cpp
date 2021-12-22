#include "include/add.h"
#include "include/mainwindow.h"
#include <QDebug>

extern MainWindow *w;

Add::Add(QWidget *parent): QMainWindow(parent), ui(new Ui::Add) {
    ui->setupUi(this);
    setWindowTitle("Add Contact");
}

Add::~Add() {
    delete ui;
}

void Add::on_add_clicked() {
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
    QByteArray encodedText = cipher->encode(jsonContactData.toJson(), key.toUtf8());
    encodedText = encodedText.toHex();
    encodedText = QUrl::toPercentEncoding(encodedText);

    delete cipher;

    QSqlDatabase db = MainWindow::SetUpDatabase();

    QSqlQuery query(db);
    query.prepare("INSERT INTO Contacts (user, data) VALUES (:user, :data)");
    query.bindValue(":user", this->id);
    query.bindValue(":data", encodedText);
    query.exec();

    db.close();
    w->MainFrame();
}

void Add::passUserData(QString un, QString key, int id) {
    this->un = un;
    this->key = key;
    this->id = id;
}



