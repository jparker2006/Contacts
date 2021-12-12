#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>

#include "ui_contactswindow.h"

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
    void passUserData(QString un, QString pw);
private:
    Ui::ContactsWindow *ui;
    QString un;
    QString pw;
};

#endif // CONTACTSWINDOW_H
