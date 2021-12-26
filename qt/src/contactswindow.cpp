#include "include/contactswindow.h"
#include "include/mainwindow.h"

extern MainWindow *w;

ContactsWindow::ContactsWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::ContactsWindow) {
    ui->setupUi(this);
    setWindowTitle("Contacts");
    setMouseTracking(true);
}

ContactsWindow::~ContactsWindow() {
    delete ui;
}

void ContactsWindow::mousePressEvent(QMouseEvent *event) {
    int nX = event->pos().x();
    int nY = event->pos().y();
    if (nX >= 10 && nX <= 220 && nY >= 10 && nY <= 74) {
        HomeFrame();
    }
}

void ContactsWindow::passUserData(QString un, QString pw, int id) {
    this->un = un;
    this->pw = pw;
    this->id = id;
}

void ContactsWindow::on_add_clicked() {
    w->AddFrame(un, pw, id);
}

void ContactsWindow::pullData() { // needs a refactor
    ui->list->clear();
    ui->s_tags->clear();
    QMap<int, QJsonObject> objAllContactData = {};
    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();

    QSqlQuery pull(db);
    pull.prepare("SELECT id, data FROM Contacts WHERE user=:id");
    pull.bindValue(":id", this->id);
    pull.exec();

    while (pull.next()) {
        QJsonDocument jsonContactData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(pull.value(1).toByteArray(), pw.toUtf8())));
        QJsonObject objContactData = jsonContactData.object();
        objAllContactData.insert(pull.value(0).toInt(), objContactData);

        if (objContactData["first"].toString().isEmpty()) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, pull.value(0).toInt());
            item->setText(objContactData["company"].toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->list->addItem(item);
        }
        else {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, pull.value(0).toInt());
            item->setText(objContactData["first"].toString() + " " + objContactData["last"].toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->list->addItem(item);
        }
    }

    db.close();
    delete cipher;
    this->objAllContactData = objAllContactData;
    pullTags();
}

void ContactsWindow::on_list_itemDoubleClicked(QListWidgetItem *item) {
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT data FROM Contacts WHERE id=:id");
    query.bindValue(":id", item->data(-1).toInt());
    query.exec();
    query.next();

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);

    QJsonDocument jsonContactData = QJsonDocument::fromJson(cipher->removePadding(cipher->decode(query.value(0).toByteArray(), pw.toUtf8())));
    QJsonObject objContactData = jsonContactData.object();

    w->EditFrame(item->data(-1).toInt(), objContactData, this->pw, this->id); // gonna be an issue
}

void ContactsWindow::on_s_first_clicked() {
    ui->s_tags->setCurrentIndex(0);
    ui->list->clear();
    QMapIterator<int, QJsonObject> iter(objAllContactData);
    while (iter.hasNext()) {
        iter.next();

        QListWidgetItem *item = new QListWidgetItem();
        item->setData(-1, iter.key());
        QJsonObject jsonCurrent = iter.value();

        if (jsonCurrent["first"].toString().isEmpty())
            item->setText(jsonCurrent["company"].toString());
        else
            item->setText(jsonCurrent["first"].toString() + " " + jsonCurrent["last"].toString());
        item->setTextAlignment(Qt::AlignCenter);
        ui->list->addItem(item);
    }
    ui->list->sortItems();
}

void ContactsWindow::on_s_last_clicked() {
    ui->s_tags->setCurrentIndex(0);
    ui->list->clear();

    QMapIterator<int, QJsonObject> iter(objAllContactData);
    while (iter.hasNext()) {
        iter.next();

        QListWidgetItem *item = new QListWidgetItem();

        item->setData(-1, iter.key());
        QJsonObject jsonCurrent = iter.value();

        if (jsonCurrent["first"].toString().isEmpty())
            item->setText(jsonCurrent["company"].toString());
        else {
            if (jsonCurrent["last"].toString().isEmpty())
                item->setText(jsonCurrent["first"].toString());
            else
                item->setText(jsonCurrent["last"].toString() + ", " + jsonCurrent["first"].toString());
        }
        item->setTextAlignment(Qt::AlignCenter);
        ui->list->addItem(item);
    }

    ui->list->sortItems();
}

void ContactsWindow::on_s_location_clicked() {
    ui->s_tags->setCurrentIndex(0);
    ui->list->clear();

    QMapIterator<int, QJsonObject> iter(objAllContactData);
    while (iter.hasNext()) {
        iter.next();

        QListWidgetItem *item = new QListWidgetItem();

        item->setData(-1, iter.key());
        QJsonObject jsonCurrent = iter.value();
        if (jsonCurrent["first"].toString().isEmpty()) {
            if (jsonCurrent["city"].toString().isEmpty() && jsonCurrent["state"].toString().isEmpty())
                item->setText(jsonCurrent["company"].toString());
            else if (!jsonCurrent["city"].toString().isEmpty() && jsonCurrent["state"].toString().isEmpty())
                item->setText(jsonCurrent["company"].toString() + ": " + jsonCurrent["city"].toString());
            else if (jsonCurrent["city"].toString().isEmpty() && !jsonCurrent["state"].toString().isEmpty())
                item->setText(jsonCurrent["company"].toString() + ": " + jsonCurrent["state"].toString());
            else
                item->setText(jsonCurrent["company"].toString() + ": " + jsonCurrent["city"].toString() + ", " + jsonCurrent["state"].toString());
        }
        else {
            if (jsonCurrent["city"].toString().isEmpty() && jsonCurrent["state"].toString().isEmpty())
                item->setText(jsonCurrent["first"].toString() + " " + jsonCurrent["last"].toString());
            else if (!jsonCurrent["city"].toString().isEmpty() && jsonCurrent["state"].toString().isEmpty())
                item->setText(jsonCurrent["first"].toString() + " " + jsonCurrent["last"].toString() + ": " + jsonCurrent["city"].toString());
            else if (jsonCurrent["city"].toString().isEmpty() && !jsonCurrent["state"].toString().isEmpty())
                item->setText(jsonCurrent["first"].toString() + " " + jsonCurrent["last"].toString() + ": " + jsonCurrent["state"].toString());
            else
                item->setText(jsonCurrent["first"].toString() + " " +
                        jsonCurrent["last"].toString() + ": " + jsonCurrent["city"].toString() + ", " + jsonCurrent["state"].toString());
        }
        item->setTextAlignment(Qt::AlignCenter);
        ui->list->addItem(item);
    }

    ui->list->sortItems();
}

void ContactsWindow::on_ajax_textChanged(const QString &sAjax) {
    ui->s_tags->setCurrentIndex(0);
    ui->list->clear();
    QMapIterator<int, QJsonObject> iter(objAllContactData);
    while (iter.hasNext()) {
        iter.next();

        int nCurrId = iter.key();
        QJsonObject objCurr = iter.value();

        if (partOfJsonInAjax(objCurr, sAjax)) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(-1, nCurrId);
            if (objCurr["first"].toString().isEmpty())
                item->setText(objCurr["company"].toString());
            else
                item->setText(objCurr["first"].toString() + " " + objCurr["last"].toString());
            item->setTextAlignment(Qt::AlignCenter);

            ui->list->addItem(item);
        }
    }
}

bool ContactsWindow::partOfJsonInAjax(QJsonObject objData, QString sAjax) {
    if (objData["first"].toString().toLower().contains(sAjax.toLower()))       return true;
    if (objData["middle"].toString().toLower().contains(sAjax.toLower()))      return true;
    if (objData["last"].toString().toLower().contains(sAjax.toLower()))        return true;
    if (objData["company"].toString().toLower().contains(sAjax.toLower()))     return true;
    if (objData["title"].toString().toLower().contains(sAjax.toLower()))       return true;
    if (objData["home"].toString().toLower().contains(sAjax.toLower()))        return true;
    if (objData["mobile"].toString().toLower().contains(sAjax.toLower()))      return true;
    if (objData["work"].toString().toLower().contains(sAjax.toLower()))        return true;
    if (objData["address"].toString().toLower().contains(sAjax.toLower()))     return true;
    if (objData["email"].toString().toLower().contains(sAjax.toLower()))       return true;
    if (objData["website"].toString().toLower().contains(sAjax.toLower()))     return true;
    if (objData["state"].toString().toLower().contains(sAjax.toLower()))       return true;
    if (objData["city"].toString().toLower().contains(sAjax.toLower()))        return true;
    if (objData["zip"].toString().toLower().contains(sAjax.toLower()))         return true;
    if (objData["birthday"].toString().toLower().contains(sAjax.toLower()))    return true;
    if (objData["anniversary"].toString().toLower().contains(sAjax.toLower())) return true;
    if (objData["notes"].toString().toLower().contains(sAjax.toLower()))       return true;
    return false;
}

void ContactsWindow::clearAjaxBox() {
    ui->ajax->clear();
}

void ContactsWindow::HomeFrame() {
    this->setWindowTitle("Home");
    // w->HomeFrame();
}

void ContactsWindow::on_createTag_clicked() {
    bool bOkClick;
    QInputDialog mInput;
    QString sTagName = mInput.getText(this, tr("Make"), tr("Tag:"), QLineEdit::EchoMode::Normal, "", &bOkClick).trimmed();

    if (!bOkClick || sTagName.isEmpty())
        return;
    if (sTagName.length() > 20) {
        QMessageBox alert;
        alert.setText("Your tag name was too long, sorry");
        alert.setWindowTitle("!sorry!");
        alert.exec();
        return;
    }
    if (sTagName.contains("~")) {
        QMessageBox alert;
        alert.setText("Tags cannot contain '~', sorry");
        alert.setWindowTitle("!sorry!");
        alert.exec();
        return;
    }

    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QByteArray baTagName = cipher->encode(sTagName.toUtf8(), this->pw.toUtf8());

    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Tags (user, name) VALUES (:user, :name)");
    query.bindValue(":user", this->id);
    query.bindValue(":name", baTagName);
    query.exec();

    db.close();
    delete cipher;
    pullTags();
}

void ContactsWindow::pullTags() {
    ui->s_tags->addItem("Tags (default)");
    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT name FROM Tags WHERE user=:user");
    query.bindValue(":user", this->id);
    query.exec();

    while (query.next()) {
        QString sCurrTag = cipher->removePadding(cipher->decode(query.value(0).toByteArray(), pw.toUtf8()));
        ui->s_tags->addItem(sCurrTag);
    }
    delete cipher;
    db.close();
}

void ContactsWindow::on_s_tags_currentTextChanged(const QString &sTag) {
    if ("Tags (default)" == sTag)
        return;

    ui->list->clear();

    QMapIterator<int, QJsonObject> iter(objAllContactData);
    while (iter.hasNext()) {
        iter.next();

        QListWidgetItem *item = new QListWidgetItem();

        item->setData(-1, iter.key());
        QJsonObject jsonCurrent = iter.value();

        QList<QString> v_tags = jsonCurrent["tags"].toString().split("~");
        bool bContains = false;
        for (int i=0; i<ui->s_tags->count(); i++) {
            if (v_tags.contains(sTag)) {
                bContains = true;
                break;
            }
        }

        if (!bContains)
            continue; // go next iter

        if (jsonCurrent["first"].toString().isEmpty())
            item->setText(jsonCurrent["company"].toString());
        else
            item->setText(jsonCurrent["first"].toString() + " " + jsonCurrent["last"].toString());
        item->setTextAlignment(Qt::AlignCenter);
        ui->list->addItem(item);
    }
}


void ContactsWindow::on_deleteTags_clicked() {
    w->DeleteTagsFrame(this->id, this->pw, this->objAllContactData);
}

