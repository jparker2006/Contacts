#include "include/contactswindow.h"
#include "include/mainwindow.h"

extern MainWindow *w;

ContactsWindow::ContactsWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::ContactsWindow) {
    ui->setupUi(this);
    setWindowTitle("Contacts");
}

ContactsWindow::~ContactsWindow() {
    delete ui;
}

void ContactsWindow::passUserData(QString un, QString pw, int id) {
    this->un = un;
    this->pw = pw;
    this->id = id;
}

void ContactsWindow::on_add_clicked() {
    w->AddFrame(un, pw, id);
}

