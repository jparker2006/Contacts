#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QJsonObject>
#include <QMap>
#include <QMouseEvent>
#include <QInputDialog>

#include "ui_contactswindow.h"
#include "crypto/qaesencryption.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class ContactsWindow;
}
QT_END_NAMESPACE

class ContactsWindow: public QMainWindow {
    Q_OBJECT
public:
    explicit ContactsWindow(QWidget *parent = nullptr);
    ~ContactsWindow();
    void passUserData(QString un, QString pw, int id);
    void pullData();
    QList<QJsonObject> fetchSortedData(QString sCatagory);
    bool partOfJsonInAjax(QJsonObject objData, QString sAjax);
    void clearAjaxBox();
    void HomeFrame();
    void mousePressEvent(QMouseEvent *event);
    void pullTags();
private slots:
    void on_add_clicked();
    void on_list_itemDoubleClicked(QListWidgetItem *item);
    void on_s_first_clicked();
    void on_s_last_clicked();
    void on_ajax_textChanged(const QString &sAjax);
    void on_s_location_clicked();
    void on_createTag_clicked();
    void on_s_tags_currentTextChanged(const QString &sTag);

private:
    Ui::ContactsWindow *ui;
    QString un;
    QString pw;
    int id;
    QMap<int, QJsonObject> objAllContactData;
};

#endif // CONTACTSWINDOW_H
