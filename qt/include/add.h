#ifndef ADD_H
#define ADD_H

#include <QMainWindow>

#include "ui_add.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Add;
}
QT_END_NAMESPACE

class Add: public QMainWindow {
    Q_OBJECT
public:
    explicit Add(QWidget *parent = nullptr);
    ~Add();
private slots:
    void on_add_clicked();
private:
    Ui::Add *ui;
};

#endif // ADD_H
