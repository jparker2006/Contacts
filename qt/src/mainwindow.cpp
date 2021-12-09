#include "include/mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    // if !cookies -> login
    LoginFrame(false);
    // else -> send to contacts
    //this->setWindowTitle("Contacts");
}

void MainWindow::LoginFrame(bool bSignIn) { // true ? delete sign in : none
    if (bSignIn)
        signup->hide();

    login->show();
}

void MainWindow::SignUpFrame(bool bLogin) {
    if (bLogin)
        login->hide();

    signup->show();
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

