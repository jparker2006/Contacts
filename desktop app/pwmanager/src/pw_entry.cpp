#include "pwmanager/include/pw_entry.h"
#include "main/include/mainwindow.h"

extern MainWindow *w;

pw_entry::pw_entry(QWidget *parent): QMainWindow(parent), ui(new Ui::pw_entry) {
    ui->setupUi(this);
    setWindowTitle("Add/Edit Password");
}

pw_entry::~pw_entry() {
    delete ui;
}

void pw_entry::a_setup() {
    this->bAdding = true;
    ui->del->hide();
    ui->add->setText("Add");
}

void pw_entry::e_setup(int id) {
    this->bAdding = false;
    this->nItemID = id;
    ui->del->show();
    ui->add->setText("Save");

    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT data FROM Passwords WHERE id=:id");
    query.bindValue(":id", this->nItemID);
    query.exec();
    query.next();

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);

    QJsonDocument jsonData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(query.value(0).toByteArray(), w->sPassword.toUtf8())));
    QJsonObject objData = jsonData.object();
    ui->title->setText(objData["title"].toString());
    ui->login->setText(objData["login"].toString());
    ui->password->setText(objData["password"].toString());
    ui->webAdress->setText(objData["web"].toString());
    ui->notes->setText(objData["notes"].toString());
}

void pw_entry::on_back_clicked() {
    w->PasswordFrame();
}

void pw_entry::on_gen_clicked() {
    ui->password->setText(GenerateRandomPassword());
}

QString pw_entry::GenerateRandomPassword() {
    QChar aChar[] =
        {'A','B','C','D','E','F','G','H','I','J',
         'K','L','M','N','O','P','Q','R','S','T',
         'U','V','W','X','Y','Z','0','1','2','3',
         '4','5','6','7','8','9', '!', '@', '#',
         '$', '%', '^', '&', '*', '(', ')', ',',
         '<', '>', '?', 'a','b','c','d','e','f',
         'g','h','i','j', 'k','l','m','n','o',
         'p','q','r','s','t', 'u','v','w','x','y','z'};
    QString sCode = "";
    for (int i=0; i<13; i++) {
        sCode += aChar[QRandomGenerator::global()->bounded(0, 76)];
    }
    return sCode;
}


void pw_entry::on_add_clicked() {
    QString sTitle = ui->title->text();
    QString sLogin = ui->login->text();
    QString sPassword = ui->password->text();
    QString sWebAdress = ui->webAdress->text();
    QString sNotes = ui->notes->toPlainText();

    if (sWebAdress.isEmpty() && sTitle.isEmpty()) {
        QMessageBox alert;
        alert.setText("Either title or web address must be filled out");
        alert.setWindowTitle("!error!");
        alert.exec();
        return;
    }

    QJsonObject objData;
    objData["title"] = sTitle;
    objData["login"] = sLogin;
    objData["password"] = sPassword;
    objData["web"] = sWebAdress;
    objData["notes"] = sNotes;

    QJsonDocument *jsonContactData = new QJsonDocument();
    jsonContactData->setObject(objData);

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QByteArray ba_jsonData = cipher->encode(jsonContactData->toJson(QJsonDocument::Compact), w->sPassword.toUtf8());

    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);

    if (bAdding) {
        query.prepare("INSERT INTO Passwords (user, data) VALUES (:user, :data)");
        query.bindValue(":user", w->id);
        query.bindValue(":data", ba_jsonData);
    }
    else {
        query.prepare("UPDATE Passwords SET data=:data WHERE id=:id");
        query.bindValue(":id", this->nItemID);
        query.bindValue(":data", ba_jsonData);
    }

    query.exec();

    db.close();
    w->PasswordFrame();
    clearTextboxes();
}

void pw_entry::clearTextboxes() {
    ui->title->clear();
    ui->login->clear();
    ui->password->clear();
    ui->webAdress->clear();
}

void pw_entry::on_del_clicked() {
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("DELETE FROM Passwords WHERE id=:id");
    query.bindValue(":id", this->nItemID);
    query.exec();
    db.close();
    w->PasswordFrame();
    clearTextboxes();
}

