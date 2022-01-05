#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QClipboard>

#include "ui_home.h"

namespace Ui {
    class Home;
}

class Home: public QMainWindow {
    Q_OBJECT
public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::Home *ui;
    QString sUsername;
    QString sPassword;
};

#endif // HOME_H
