#ifndef ENTRY_H
#define ENTRY_H

#include <QMainWindow>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPushButton>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>

#include "ui_entry.h"

namespace Ui {
    class Entry;
}

class Entry: public QMainWindow {
    Q_OBJECT
public:
    explicit Entry(QWidget *parent = nullptr);
    ~Entry();

    void a_passData();
    void a_removeDeleteButton();

    void e_passData(QJsonObject objContactData, int nItemId);
    void e_setupData();
    void e_addDeleteButton();

    void clearTextboxes();
    QJsonObject fetchJsonData(QString sFirst, QString sCompany);
    void setUpTags();
    int enterImage();

private slots:
    void enterData();
    void back_clicked();
    void e_deleteData();
    void on_imageBtn_clicked();

private:
    Ui::Entry *ui;
    int nItemId;
    QJsonObject objContactData;
    bool bAdding; // true if on adding frame
    QPixmap px_scaledImage;
    bool bImageSelected;
};

#endif // ENTRY_H
