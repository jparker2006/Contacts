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

    if (x >= 526 && x<= 590 && y >= 5 && y <= 69)
        w->AccountSettingsFrame();

    if (x >= 165 && x<= 435 && y >= 144 && y <= 244)
        w->ContactsFrame();
}

void Home::setupPFP(QString sPassword) { // temp
    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT picture FROM Images WHERE id=:id");
    query.bindValue(":id", MainWindow::LoadImageCookie());
    query.exec();
    query.next();

    QByteArray bArray = cipher->removePadding(cipher->decode(query.value(0).toByteArray(), sPassword.toUtf8()));
    QImage img = QImage::fromData(bArray);
    ui->accountSettings->setPixmap(QPixmap::fromImage(img).scaled(64, 64));

    db.close();
    delete cipher;
}

