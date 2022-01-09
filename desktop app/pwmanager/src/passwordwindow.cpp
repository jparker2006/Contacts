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

void PasswordWindow::pullData() {
    ui->list->clear();
    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();

    QSqlQuery pull(db);
    pull.prepare("SELECT id, data FROM Passwords WHERE user=:id");
    pull.bindValue(":id", w->id);
    pull.exec();

    while (pull.next()) {
        QJsonDocument jsonContactData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(pull.value(1).toByteArray(), w->sPassword.toUtf8())));
        QJsonObject objContactData = jsonContactData.object();

        if (objContactData["title"].toString().isEmpty()) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, pull.value(0).toInt());
            item->setText(objContactData["web"].toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->list->addItem(item);
        }
        else {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, pull.value(0).toInt());
            item->setText(objContactData["title"].toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->list->addItem(item);
        }
    }

    db.close();
    delete cipher;
}

void PasswordWindow::on_list_itemDoubleClicked(QListWidgetItem *item) {
    int nItemId = item->data(-1).toInt();
    w->PW_EditFrame(nItemId);
}


void PasswordWindow::on_ajax_textChanged(const QString &sQuery) {
    ui->list->clear();
    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();

    QSqlQuery pull(db);
    pull.prepare("SELECT id, data FROM Passwords WHERE user=:id");
    pull.bindValue(":id", w->id);
    pull.exec();

    while (pull.next()) {
        QJsonDocument jsonData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(pull.value(1).toByteArray(), w->sPassword.toUtf8())));
        QJsonObject objData = jsonData.object();
        bool bIncludes = false;
        if (objData["title"].toString().contains(sQuery))        bIncludes = true;
        if (objData["login"].toString().contains(sQuery))        bIncludes = true;
        if (objData["password"].toString().contains(sQuery))     bIncludes = true;
        if (objData["web"].toString().contains(sQuery))          bIncludes = true;
        if (objData["notes"].toString().contains(sQuery))        bIncludes = true;
        if (!bIncludes) continue;

        if (objData["title"].toString().isEmpty()) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, pull.value(0).toInt());
            item->setText(objData["web"].toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->list->addItem(item);
        }
        else {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, pull.value(0).toInt());
            item->setText(objData["title"].toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->list->addItem(item);
        }
    }

    db.close();
    delete cipher;
}

