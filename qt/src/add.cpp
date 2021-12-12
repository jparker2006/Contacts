#include "include/add.h"


Add::Add(QWidget *parent): QMainWindow(parent), ui(new Ui::Add) {
    ui->setupUi(this);
    setWindowTitle("Add Contact");
}

Add::~Add() {
    delete ui;
}

void Add::on_add_clicked() {
    // grab all tb data
    // make sure either company or first is filled out
}

