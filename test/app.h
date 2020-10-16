#ifndef APP_H
#define APP_H

#include <QApplication>
#include "serverapi.h"
#include "logindlg.h"
#include "mainwnd.h"

class App : public QApplication
{
public:
    App(int &argc, char **argv);

    void showLoginDlg();
    void showMainWnd();

public:
    ServerApi serverApi;
    LoginDlg loginDlg;
    Mainwnd mainWnd;
};
extern App *g_app;
#endif // APP_H
