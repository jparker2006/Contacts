#ifndef DELETETAGS_H
#define DELETETAGS_H

#include "ui_deletetags.h"

namespace Ui {
    class DeleteTags;
}

class DeleteTags: public QMainWindow {
    Q_OBJECT

public:
    explicit DeleteTags(QWidget *parent = nullptr);
    ~DeleteTags();
    void passData(QMap<int, QJsonObject> objAllData);
    void pullListData();
    void deleteTagFromAllUsers(QString sTag);
    void deleteTag(int nTagId);
private slots:
    void on_back_clicked();
    void on_confirm_clicked();

private:
    Ui::DeleteTags *ui;
    QMap<int, QJsonObject> objData;
};

#endif // DELETETAGS_H
