#include "passman/include/passwordwindow.h"
#include "main/include/mainwindow.h"

extern MainWindow *w;

PasswordWindow::PasswordWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::PasswordWindow) {
    ui->setupUi(this);
    setWindowTitle("Password Manager");
}

PasswordWindow::~PasswordWindow() {
    delete ui;
}

void PasswordWindow::mousePressEvent(QMouseEvent *event) {
    int nX = event->pos().x();
    int nY = event->pos().y();
    if (nX >= 776 && nX <= 840 && nY >= 10 && nY <= 74)
        w->HomeFrame();
}
