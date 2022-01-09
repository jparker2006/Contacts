#include "pwmanager/include/pw_entry.h"
#include "main/include/mainwindow.h"

extern MainWindow *w;

pw_entry::pw_entry(QWidget *parent): QMainWindow(parent), ui(new Ui::pw_entry) {
    ui->setupUi(this);
    setWindowTitle("Add/Edit Password");
}

pw_entry::~pw_entry() {
    delete ui;
}

void pw_entry::on_back_clicked() {
    w->PasswordFrame();
}

void pw_entry::on_gen_clicked() {
    ui->password->setText(GenerateRandomPassword());
}

QString pw_entry::GenerateRandomPassword() {
    QChar aChar[] =
        {'A','B','C','D','E','F','G','H','I','J',
         'K','L','M','N','O','P','Q','R','S','T',
         'U','V','W','X','Y','Z','0','1','2','3',
         '4','5','6','7','8','9', '!', '@', '#',
         '$', '%', '^', '&', '*', '(', ')', ',',
         '<', '>', '?', 'a','b','c','d','e','f',
         'g','h','i','j', 'k','l','m','n','o',
         'p','q','r','s','t', 'u','v','w','x','y','z'};
    QString sCode = "";
    for (int i=0; i<13; i++) {
        sCode += aChar[QRandomGenerator::global()->bounded(0, 76)];
    }
    return sCode;
}

