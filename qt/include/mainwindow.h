#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QIcon>

#include "include/login.h"
#include "include/signup.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void LoginFrame(bool bSignIn);
    void SignUpFrame(bool bLogin);
    void MainFrame();


// private slots:
//    void on_list_itemDoubleClicked(QListWidgetItem *item);
//    void on_add_clicked();
    //    void on_ajax_textChanged(const QString &arg1);


private:
    SignUp *signup = new SignUp();
    Login *login = new Login();
};
#endif // MAINWINDOW_H
