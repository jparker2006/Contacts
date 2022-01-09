#ifndef HOME_H
#define HOME_H

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
    void setupPFP(QString sPassword);

private:
    Ui::Home *ui;
};

#endif // HOME_H
