#include "account/include/accountsettings.h"
#include "main/include/mainwindow.h"

extern MainWindow *w;


AccountSettings::AccountSettings(QWidget *parent): QMainWindow(parent), ui(new Ui::AccountSettings) {
    ui->setupUi(this);
    this->setWindowTitle("Account Settings");
}

AccountSettings::~AccountSettings() {
    delete ui;
}

void AccountSettings::setupData() {
    ui->first->setText(w->sFirst);
    ui->last->setText(w->sLast);

    if (0 == MainWindow::LoadImageCookie()) {
        bEditing = false;
        return;
    }

    bEditing = true;
    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT picture FROM Images WHERE id=:id");
    query.bindValue(":id", MainWindow::LoadImageCookie());
    query.exec();
    query.next();

    QByteArray bArray = cipher->removePadding(cipher->decode(query.value(0).toByteArray(), w->sPassword.toUtf8()));
    QImage img = QImage::fromData(bArray);

    ui->imageDisplay->setPixmap(QPixmap::fromImage(img));
    this->px_image = QPixmap::fromImage(img);
    delete cipher;
}

void AccountSettings::on_back_clicked() {
    w->HomeFrame();
}

void AccountSettings::on_confirm_user_data_clicked() {
    QString sFirst = ui->first->text().trimmed();
    QString sLast = ui->last->text().trimmed();

    MainWindow::SaveCookies(w->sUsername, w->sPassword, sFirst, sLast);

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QByteArray ba_first = cipher->encode(sFirst.toUtf8(), w->sPassword.toUtf8());
    QByteArray ba_last = cipher->encode(sLast.toUtf8(), w->sPassword.toUtf8());

    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("UPDATE Users SET first=:first, last=:last WHERE id=:id");
    query.bindValue(":first", ba_first);
    query.bindValue(":last", ba_last);
    query.bindValue(":id", w->id);
    query.exec();
    db.close();

    w->HomeFrame();
}

void AccountSettings::on_select_image_clicked() {
    QString sFileName = QFileDialog::getOpenFileName(this, tr("Choose file"), "", tr("Images (*.jpg)"));
    if (sFileName.isEmpty())
        return;

    QImage image;
    bool bValid = image.load(sFileName);
    if (!bValid)
        return;
    this->px_image = QPixmap::fromImage(image).scaled(200, 200);
    ui->imageDisplay->setPixmap(px_image);
}

void AccountSettings::on_confirm_image_clicked() {
    if (this->px_image.isNull())
        return;

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);

    if (this->bEditing) {
        query.prepare("UPDATE Images SET picture=:data WHERE id=:id");
        query.bindValue(":id", MainWindow::LoadImageCookie());
    }
    else {
        query.prepare("INSERT INTO Images (user, picture) VALUES (:id, :data)");
        query.bindValue(":id", w->id);
    }

    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);

    px_image.save(&buffer, "JPG");

    bArray = cipher->encode(bArray, w->sPassword.toUtf8());

    query.bindValue(":data", bArray);
    query.exec();
    query.clear();

    query.prepare("SELECT id FROM Images WHERE user=:id AND picture=:picture");
    query.bindValue(":id", w->id);
    query.bindValue(":picture", bArray);
    query.exec();
    query.next();

    MainWindow::ImageCookie(query.value(0).toInt());
    w->HomeFrame();
}


void AccountSettings::on_del_clicked() {
    bool bOkClick;
    QInputDialog mInput;
    QString sPassword = mInput.getText(
               this, tr("Confirm"),
               tr("Be careful! This action is irreversible. Type your password to confirm deletion"),
               QLineEdit::EchoMode::Normal, "", &bOkClick).trimmed();

    if (!bOkClick || sPassword.isEmpty())
        return;

    SHA3 hasher;
    std::string sHashedPW = sPassword.toStdString();
    for (int i=0; i<20000; i++) {
        sHashedPW = hasher(sHashedPW);
    }
    if (QString::fromStdString(sHashedPW) != w->sPassword) {
        QMessageBox a;
        a.setText("Password was wrong");
        a.exec();
        return;
    }

    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);

    query.prepare("DELETE FROM Images WHERE user=:id");
    query.bindValue(":id", w->id);
    query.exec();
    query.clear();

    query.prepare("DELETE FROM Tags WHERE user=:id");
    query.bindValue(":id", w->id);
    query.exec();
    query.clear();

    query.prepare("DELETE FROM Contacts WHERE user=:id");
    query.bindValue(":id", w->id);
    query.exec();
    query.clear();

    query.prepare("DELETE FROM Users WHERE id=:id");
    query.bindValue(":id", w->id);
    query.exec();

    db.close();

    MainWindow::ClearCookies();
    MainWindow::ImageCookie(0);

    w->SignUpFrame();
}

