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
private:
    Ui::PasswordWindow *ui;
};

#endif // PASSWORDWINDOW_H
