#include "include/login.h"
#include "include/mainwindow.h"

extern MainWindow *w;

Login::Login(QWidget *parent): QMainWindow(parent), ui(new Ui::Login) {
    ui->setupUi(this);
    this->setWindowTitle("Login");
}

Login::~Login() {
    delete ui;
}

void Login::on_signup_clicked() {
    w->SignUpFrame(true);
}

