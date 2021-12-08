#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_list_itemDoubleClicked(QListWidgetItem *item);
    void on_add_clicked();
    void on_ajax_textChanged(const QString &arg1);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
