#include "contacts/include/deletetags.h"
#include "main/include/mainwindow.h"

extern MainWindow *w;

DeleteTags::DeleteTags(QWidget *parent): QMainWindow(parent), ui(new Ui::DeleteTags) {
    ui->setupUi(this);
    setWindowTitle("Deleting Tags");
}

DeleteTags::~DeleteTags() {
    delete ui;
}

void DeleteTags::passData(int nId, QString sKey, QMap<int, QJsonObject> objAllData) {
    this->nId = nId;
    this->sKey = sKey;
    this->objData = objAllData;
    pullListData();
}

void DeleteTags::pullListData() {
    ui->list->clear();
    QAESEncryption *cipher = new QAESEncryption(QAESEncryption::AES_256, QAESEncryption::ECB, QAESEncryption::PKCS7);
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT id, name FROM Tags WHERE user=:user");
    query.bindValue(":user", this->nId);
    query.exec();

    while (query.next()) {
        QString sCurrTag = cipher->removePadding(cipher->decode(query.value(1).toByteArray(), this->sKey.toUtf8()));
        QListWidgetItem *currItem = new QListWidgetItem();
        currItem->setFlags(currItem->flags() | Qt::ItemIsUserCheckable);
        currItem->setCheckState(Qt::Unchecked);
        currItem->setText(sCurrTag);
        currItem->setTextAlignment(Qt::AlignLeft);
        currItem->setData(-1, query.value(0).toInt());
        ui->list->addItem(currItem);
    }
    delete cipher;
    db.close();
}

void DeleteTags::on_back_clicked() {
    w->MainFrame();
}

void DeleteTags::on_confirm_clicked() {
    for (int i=0; i<ui->list->count(); i++) {
        if (ui->list->item(i)->checkState())
            deleteTag(ui->list->item(i)->data(-1).toInt());
    }
    w->MainFrame();
}

void DeleteTags::deleteTag(int nTagId) { // might have to individually remove tag from all contacts
    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery query(db);
    query.prepare("DELETE FROM Tags WHERE id=:id");
    query.bindValue(":id", nTagId);
    query.exec();
}




