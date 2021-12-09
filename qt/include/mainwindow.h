#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

#include "include/login.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void LoginFrame();
    void MainFrame();
// private slots:
//    void on_list_itemDoubleClicked(QListWidgetItem *item);
//    void on_add_clicked();
//    void on_ajax_textChanged(const QString &arg1);
};
#endif // MAINWINDOW_H
