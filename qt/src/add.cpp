#include "include/add.h"
#include "include/mainwindow.h"
#include <QDebug>

#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/secblock.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <iostream>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>

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

    std::string text = jsonContactData.toJson(QJsonDocument::Compact).toStdString();
    std::string sKey = this->key.left(this->key.length() / 2).toStdString();
    std::string iv = this->key.right(this->key.length() / 2).toStdString();

    QMessageBox *alert = new QMessageBox();

    std::string cipher = encrypt(text, sKey, iv);

    alert->setText(QString::fromStdString(cipher));
    alert->exec();

    std::string dec = decrypt(cipher, sKey, iv);
    alert->setText(QString::fromStdString(dec));
    alert->exec();

    return;


//    QSqlDatabase db = MainWindow::SetUpDatabase();

//    QSqlQuery query(db);
//    query.prepare("INSERT INTO Contacts (user, data) VALUES (:user, :data)");
//    query.bindValue(":user", this->id);
//    query.bindValue(":data", encodedText);
//    query.exec();

//    db.close();
//    w->MainFrame();
}

std::string Add::encrypt(const std::string& str_in, const std::string& key, const std::string& iv) {
    std::string str_out;
    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption(key, key.length(), iv); // cant be byte arrays or wont sync w js
    CryptoPP::StringSource encryptor(str_in, true, new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::StringSink(str_out), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING));
    return str_out;
}


std::string Add::decrypt(const std::string& str_in, const std::string& key, const std::string& iv) {
    std::string str_out;
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption(key, key.length(), iv); // cant be byte arrays or wont sync w js
    CryptoPP::StringSource decryptor(str_in, true, new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(str_out)));
    return str_out;
}


void Add::passUserData(QString un, QString key, int id) {
    this->un = un;
    this->key = key;
    this->id = id;
}
