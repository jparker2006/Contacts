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

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.112");
    db.setDatabaseName("Contacts");
    db.setUserName("jake_contacts");
    db.setPassword("Yv9zEtKfr5yMPgkvWa4v9N");
    db.open();

    SHA3 hasher;
    std::string sHashedUN = sUsername.toStdString();
    for (int i=0; i<10000; i++) {
        sHashedUN = hasher(sHashedUN);
    }

    QSqlQuery q_unique("SELECT * FROM Users WHERE username='" + QString::fromStdString(sHashedUN) + "'");
    if (q_unique.next()) {
        ui->label->setText("username taken");
        return;
    }

    std::string sHashedPW = sPassword.toStdString();
    for (int i=0; i<10000; i++) {
        sHashedPW = hasher(sHashedPW);
    }

    MainWindow::SaveCookies(QString::fromStdString(sHashedUN), QString::fromStdString(sHashedPW));

    for (int i=0; i<20000; i++) {
        sHashedPW = hasher(sHashedPW);
    }

    QSqlQuery q_insert(db);
    q_insert.prepare("INSERT INTO Users (username, password) VALUES (:username, :password)");
    q_insert.bindValue(":username", QString::fromStdString(sHashedUN));
    q_insert.bindValue(":password", QString::fromStdString(sHashedPW));
    q_insert.exec();
    db.close();
    ui->label->setText("account created!");
}


void SignUp::on_login_clicked() {
    w->LoginFrame(true);
}

