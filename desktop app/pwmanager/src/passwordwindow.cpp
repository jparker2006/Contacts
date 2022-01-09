#include "pwmanager/include/passwordwindow.h"
#include "main/include/mainwindow.h"

extern MainWindow *w;

PasswordWindow::PasswordWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::PasswordWindow) {
    ui->setupUi(this);
    setWindowTitle("Password Manager");

    connect(ui->add, &QPushButton::clicked, this, &PasswordWindow::addItem);
}

PasswordWindow::~PasswordWindow() {
    delete ui;
}

void PasswordWindow::mousePressEvent(QMouseEvent *event) {
    int nX = event->pos().x();
    int nY = event->pos().y();
    if (nX >= 626 && nX <= 690 && nY >= 426 && nY <= 490)
        w->HomeFrame();
}

void PasswordWindow::addItem() {
    w->PW_AddFrame();
}
