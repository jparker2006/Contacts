#ifndef ACCOUNTSETTINGS_H
#define ACCOUNTSETTINGS_H

#include "ui_accountsettings.h"

namespace Ui {
    class AccountSettings;
}

class AccountSettings: public QMainWindow {
    Q_OBJECT

public:
    explicit AccountSettings(QWidget *parent = nullptr);
    ~AccountSettings();

    void setupData();
private slots:
    void on_back_clicked();

    void on_confirm_user_data_clicked();

    void on_select_image_clicked();

    void on_confirm_image_clicked();

    void on_del_clicked();

private:
    Ui::AccountSettings *ui;
    QPixmap px_image;
    bool bEditing;
};

#endif // ACCOUNTSETTINGS_H
