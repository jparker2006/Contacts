#include "include/mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    // if !cookies -> login
    LoginFrame();
    // else -> send to contacts
    //this->setWindowTitle("Contacts");
}

void MainWindow::LoginFrame() {
    Login *login = new Login();
    login->show();
}

void MainWindow::MainFrame() {
    return;
}

//void MainWindow::on_list_itemDoubleClicked(QListWidgetItem *item) {
//    item->setText("poopy");
//}

//void MainWindow::on_add_clicked() {
//    ui->list->addItem("jake parker");
//}

//void MainWindow::on_ajax_textChanged(const QString &sAjax) {
//    ui->list->addItem(sAjax); // ajax db
//}

