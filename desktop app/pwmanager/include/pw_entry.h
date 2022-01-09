#ifndef PW_ENTRY_H
#define PW_ENTRY_H

#include "ui_pw_entry.h"

namespace Ui {
    class pw_entry;
}

class pw_entry: public QMainWindow {
    Q_OBJECT
public:
    explicit pw_entry(QWidget *parent = nullptr);
    ~pw_entry();
    QString GenerateRandomPassword();
private slots:
    void on_back_clicked();
    void on_gen_clicked();
private:
    Ui::pw_entry *ui;
};

#endif // PW_ENTRY_H
