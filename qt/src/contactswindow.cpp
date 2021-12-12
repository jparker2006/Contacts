#include "include/contactswindow.h"

ContactsWindow::ContactsWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::ContactsWindow) {
    ui->setupUi(this);
    setWindowTitle("Contacts");
}

ContactsWindow::~ContactsWindow() {
    delete ui;
}

void ContactsWindow::passUserData(QString un, QString pw) {
    this->un = un;
    this->pw = pw;
}
