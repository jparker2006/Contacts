#include "include/login.h"
#include "SHA256/include/SHA256.h"

Login::Login(QWidget *parent): QMainWindow(parent), ui(new Ui::Login) {
    ui->setupUi(this);
    this->setFixedSize(600, 500);
    this->setWindowTitle("Login");
}

Login::~Login() {
    delete ui;
}

void Login::on_create_clicked() {
    QString sUsername = ui->username->text();
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

    std::string sUN = sUsername.toStdString();
    SHA256 hasher;
    hasher.update(sUN);
    uint8_t *digest = hasher.digest();
    ui->label->setText(QString::fromStdString(SHA256::toString(digest)));
    delete[] digest;
}

