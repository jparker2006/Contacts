#ifndef PASSWORDWINDOW_H
#define PASSWORDWINDOW_H

#include "ui_passwordwindow.h"

namespace Ui {
    class PasswordWindow;
}

class PasswordWindow: public QMainWindow {
    Q_OBJECT
public:
    explicit PasswordWindow(QWidget *parent = nullptr);
    ~PasswordWindow();
    void mousePressEvent(QMouseEvent *event);
    void addItem();
    void pullData();
private slots:
    void on_list_itemDoubleClicked(QListWidgetItem *item);

    void on_ajax_textChanged(const QString &arg1);

private:
    Ui::PasswordWindow *ui;
};

#endif // PASSWORDWINDOW_H
