#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include "ui_login.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Login;
}
QT_END_NAMESPACE

class Login: public QMainWindow {
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
private slots:
    void on_signup_clicked();
    void on_login_clicked();
private:
    Ui::Login *ui;
};

#endif // LOGIN_H
