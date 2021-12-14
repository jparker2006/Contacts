#ifndef ADD_H
#define ADD_H

#include <QMainWindow>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "ui_add.h"
#include "crypto/qaesencryption.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Add;
}
QT_END_NAMESPACE

class Add: public QMainWindow {
    Q_OBJECT
public:
    explicit Add(QWidget *parent = nullptr);
    ~Add();
    void passUserData(QString un, QString pw, int id);
private slots:
    void on_add_clicked();
private:
    Ui::Add *ui;
    int id;
    QString un;
    QString key;
};

#endif // ADD_H
