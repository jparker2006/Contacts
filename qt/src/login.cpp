#include "include/login.h"
#include <QPasswordDigestor>

Login::Login(QWidget *parent): QMainWindow(parent), ui(new Ui::Login) {
    ui->setupUi(this);
    this->setFixedSize(600, 500);
    this->setWindowTitle("Login");
}

Login::~Login() {
    delete ui;
}

void Login::on_create_clicked() {
    const QString sUsername = ui->username->text();
    const QString sPassword = ui->password->text();
    const QString sConfirm = ui->confirm->text();

    if (sUsername.isEmpty() || sPassword.isEmpty() || sConfirm.isEmpty()) {
        ui->label->setText("fill out all fields");
        return;
    }
    if (sPassword != sConfirm) {
        ui->label->setText("please match passwords");
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.112");
    db.setDatabaseName("Contacts");
    db.setUserName("jake");
    db.setPassword("h0p@WwzVGroXeg9");
    db.open();

    QSqlQuery query(db);
    query.prepare("INSERT INTO Users (username, password) VALUES (:username, :password)");

    QCryptographicHash *hasher = new QCryptographicHash(QCryptographicHash::RealSha3_256);
    hasher->addData(sUsername.toUtf8());
    query.bindValue(":username", hasher->result().toBase64());
    hasher->reset();

    hasher->addData(sPassword.toUtf8());
    query.bindValue(":password", hasher->result().toBase64());
    hasher->reset();

    query.exec();
    db.close();

    ui->label->setText("Account Created");
}



