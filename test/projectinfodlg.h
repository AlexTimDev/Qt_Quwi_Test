#ifndef PROJECTINFODLG_H
#define PROJECTINFODLG_H

#include <QDialog>

namespace Ui {
class ProjectInfoDlg;
}

class ProjectInfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectInfoDlg(QWidget *parent = nullptr);
    ~ProjectInfoDlg();

    void setProjectId(int id);

protected:
    void showEvent(QShowEvent *event);

signals:
    void updatedName(int, QString);

protected slots:
    void on_okBtn_clicked();

private:
    Ui::ProjectInfoDlg *ui;
    int m_projId;
};

#endif // PROJECTINFODLG_H
