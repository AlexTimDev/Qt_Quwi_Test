#ifndef MAINWND_H
#define MAINWND_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Mainwnd; }
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class ProjectInfoDlg;

class Mainwnd : public QMainWindow
{
    Q_OBJECT

public:
    Mainwnd(QWidget *parent = nullptr);
    ~Mainwnd();

    void loadProjects();

protected:
    void showEvent(QShowEvent *event);
private slots:
    void on_projectItem_clicked(int id);
    void on_projectsBtn_clicked();
    void on_logoutBtn_clicked();

private:
    Ui::Mainwnd *ui;
    QScrollArea *scrollArea;
    ProjectInfoDlg *m_pProjInfoDlg;
};
#endif // MAINWND_H
