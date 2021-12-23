#ifndef ENTRY_H
#define ENTRY_H

#include <QMainWindow>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPushButton>

#include "ui_entry.h"

namespace Ui {
    class Entry;
}

class Entry: public QMainWindow {
    Q_OBJECT
public:
    explicit Entry(QWidget *parent = nullptr);
    ~Entry();

    void a_passData(QString sUn, QString sKey, int nId);
    void e_passData(QJsonObject objContactData, QString sKey, int nId);
    void e_setupData();

    void clearTextboxes();
    void a_removeDeleteButton();
    void e_addDeleteButton();
    QJsonObject fetchJsonData(QString sFirst, QString sCompany);
private slots:
    void enterData();
    void back_clicked();
    void e_deleteData();

private:
    Ui::Entry *ui;
    int nUserId;
    int nItemId;
    QString sKey;
    QString sUn;
    QJsonObject objContactData;
    bool bAdding; // true if on adding frame
};

#endif // ENTRY_H
