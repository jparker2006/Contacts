#include "include/signup.h"
#include "include/mainwindow.h"
#include "crypto/sha3.h"

extern MainWindow *w;

SignUp::SignUp(QWidget *parent): QMainWindow(parent), ui(new Ui::SignUp) {
    ui->setupUi(this);
    this->setWindowTitle("Sign Up");
}

SignUp::~SignUp() {
    delete ui;
}

void SignUp::on_create_clicked() {
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

    SHA3 hasher;

    std::string sHashedUN = hasher(sPassword.toStdString());
    setWindowTitle(QString::fromStdString(sHashedUN));
//    qDebug() << sHashedUN;

    return;

//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("192.168.1.112");
//    db.setDatabaseName("Contacts");
//    db.setUserName("jake");
//    db.setPassword("h0p@WwzVGroXeg9");
//    db.open();

//    QCryptographicHash *hasher = new QCryptographicHash(QCryptographicHash::RealSha3_256);
//    hasher->addData(sUsername.toUtf8());
//    QString sHashedUN = hasher->result().toBase64();
//    hasher->reset();

//    QSqlQuery q_unique("SELECT * FROM Users WHERE username='" + sHashedUN + "'");
//    if (q_unique.next()) {
//        ui->label->setText("username taken");
//        return;
//    }

//    QSqlQuery q_insert(db);
//    q_insert.prepare("INSERT INTO Users (username, password) VALUES (:username, :password)");
//    q_insert.bindValue(":username", sHashedUN);

//    hasher->addData(sPassword.toUtf8());
//    q_insert.bindValue(":password", hasher->result().toBase64());
//    hasher->reset();

//    q_insert.exec();
//    db.close();

//    ui->label->setText("account created!");
}


void SignUp::on_login_clicked() {
    w->LoginFrame(true);
}

