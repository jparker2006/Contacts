#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include "ui_login.h"

namespace Ui {
    class Login;
}

class Login: public QMainWindow {
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
private slots:
    void on_create_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
