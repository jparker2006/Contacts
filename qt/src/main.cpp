#include "include/mainwindow.h"
MainWindow *w;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/windowicon128.png"));
    w = new MainWindow();
    return a.exec();
}
