#ifndef EDIT_H
#define EDIT_H

#include <QMainWindow>
#include <QJsonObject>

#include "ui_edit.h"

namespace Ui {
    class Edit;
}

class Edit: public QMainWindow {
    Q_OBJECT

public:
    explicit Edit(QWidget *parent = nullptr);
    ~Edit();
    void passData(int id, QJsonObject objData, QString key);
    void setupContactData();
private slots:
    void on_b_back_clicked();
    void on_b_delete_clicked();

    void on_add_clicked();

private:
    Ui::Edit *ui;
    QJsonObject objContactData;
    int nId;
    QString key;
};

#endif // EDIT_H
