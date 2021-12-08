#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Contacts");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_list_itemDoubleClicked(QListWidgetItem *item) {
    item->setText("poopy");
}

void MainWindow::on_add_clicked() {
    ui->list->addItem("jake parker");
}

void MainWindow::on_ajax_textChanged(const QString &sAjax) {
    ui->list->addItem(sAjax); // ajax db
}

