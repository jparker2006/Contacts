#include "main/include/home.h"
#include "main/include/mainwindow.h"

extern MainWindow *w;

Home::Home(QWidget *parent): QMainWindow(parent), ui(new Ui::Home) {
    ui->setupUi(this);
    this->setWindowTitle("Home");
}

Home::~Home() {
    delete ui;
}

void Home::mousePressEvent(QMouseEvent *event) {
    int x = event->pos().x();
    int y = event->pos().y();

    if (x >= 437 && x<= 501 && y >= 5 && y <= 69) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText("https://github.com/jparker2006/EncryptedStorage");
        QMessageBox alert;
        alert.setWindowTitle("See The Code");
        alert.setText("GitHub link is copied to your clipboard");
        alert.exec();
    }

    if (x >= 165 && x<= 435 && y >= 144 && y <= 244)
        w->ContactsFrame();
}
