#include "include/edit.h"
#include "include/mainwindow.h"
extern MainWindow *w;

Edit::Edit(QWidget *parent): QMainWindow(parent), ui(new Ui::Edit) {
    ui->setupUi(this);
    setWindowTitle("Editing"); // maybe make this contacts name
}

Edit::~Edit() {
    delete ui;
}

void Edit::passData(int id, QJsonObject objData) {
    this->nId = id;
    this->objContactData = objData;
    setupContactData();
}

void Edit::setupContactData() {
    ui->first->setText(objContactData["first"].toString({""}));
    ui->middle->setText(objContactData["middle"].toString({""}));
    ui->last->setText(objContactData["last"].toString({""}));
    ui->title->setText(objContactData["title"].toString({""}));
    ui->home->setText(objContactData["home"].toString({""}));
    ui->mobile->setText(objContactData["mobile"].toString({""}));
    ui->work->setText(objContactData["work"].toString({""}));
    ui->adress->setText(objContactData["adress"].toString({""}));
    ui->email->setText(objContactData["email"].toString({""}));
    ui->website->setText(objContactData["website"].toString({""}));
    ui->state->setText(objContactData["state"].toString({""}));
    ui->city->setText(objContactData["city"].toString({""}));
    ui->zip->setText(objContactData["zip"].toString({""}));
    ui->birthday->setText(objContactData["birthday"].toString({""}));
    ui->anniversary->setText(objContactData["anniversary"].toString({""}));
    ui->notes->setText(objContactData["notes"].toString({""}));
}

void Edit::on_b_back_clicked() {
    w->MainFrame();
}

void Edit::on_b_delete_clicked() {
    QMessageBox *confirm = new QMessageBox();
    confirm->setWindowTitle("Deleting Contact"); // make contact name?
    confirm->setText("Are you sure you want to delete this contact forever?");
    confirm->setStandardButtons(QMessageBox::Yes);
    confirm->addButton(QMessageBox::No);
    confirm->setDefaultButton(QMessageBox::No);
    if (QMessageBox::No == confirm->exec())
      return;

    QSqlDatabase db = MainWindow::SetUpDatabase();
    QSqlQuery deleteQuery(db);
    deleteQuery.prepare("DELETE FROM Contacts WHERE id=:id");
    deleteQuery.bindValue(":id", this->nId);
    deleteQuery.exec();
    db.close();
    w->MainFrame();
}


