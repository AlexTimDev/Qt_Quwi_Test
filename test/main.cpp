// #include <QApplication>
#include "app.h"

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    App a(argc, argv);
    a.showLoginDlg();
    return a.exec();
}
