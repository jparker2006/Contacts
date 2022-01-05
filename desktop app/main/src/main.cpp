#include "main/include/mainwindow.h"
MainWindow *w;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/mainLogo64.png"));
    w = new MainWindow();
    return a.exec();
}
