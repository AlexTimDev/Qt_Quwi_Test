#include "app.h"

App *g_app;
App::App(int &argc, char **argv)
    :QApplication(argc, argv)
{
    g_app = this;
}
void App::showLoginDlg() {
    mainWnd.close();
    if (loginDlg.exec() == QDialog::Accepted) {
        showMainWnd();
    } else {
        quit();
    }
}
void App::showMainWnd() {
    loginDlg.close();
    mainWnd.show();
}
