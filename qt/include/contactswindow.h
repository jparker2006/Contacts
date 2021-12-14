#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "ui_contactswindow.h"
#include "crypto/qaesencryption.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class ContactsWindow;
}
QT_END_NAMESPACE

class ContactsWindow: public QMainWindow {
    Q_OBJECT
public:
    explicit ContactsWindow(QWidget *parent = nullptr);
    ~ContactsWindow();
    void passUserData(QString un, QString pw, int id);
    void pullData();
private slots:
    void on_add_clicked();
private:
    Ui::ContactsWindow *ui;
    QString un;
    QString pw;
    int id;
};

#endif // CONTACTSWINDOW_H
