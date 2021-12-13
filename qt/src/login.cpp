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

void Login::on_login_clicked() {
    const QString sUsername = ui->username->text();
    const QString sPassword = ui->password->text();

    if (sUsername.isEmpty() || sPassword.isEmpty()) {
        ui->label->setText("fill out all fields");
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


    std::string sHashedPW = sPassword.toStdString();
    for (int i=0; i<20000; i++) {
        sHashedPW = hasher(sHashedPW);
    }

    QString sCookiesPw = QString::fromStdString(sHashedPW);

    MainWindow::SaveCookies(QString::fromStdString(sHashedUN), QString::fromStdString(sHashedPW));

    for (int i=0; i<10000; i++) {
        sHashedPW = hasher(sHashedPW);
    }

    QSqlQuery q_login(db);
    q_login.prepare("SELECT * FROM Users WHERE username=:username AND password=:password");
    q_login.bindValue(":username", QString::fromStdString(sHashedUN));
    q_login.bindValue(":password", QString::fromStdString(sHashedPW));
    q_login.exec();
    1 == q_login.size() ? w->MainFrame(QString::fromStdString(sHashedUN), sCookiesPw) : ui->label->setText("login failed");
    db.close();
}

