#include "mainwnd.h"
#include "ui_mainwnd.h"
#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QScrollArea>
#include <QScrollBar>
#include <QPushButton>
#include <QMessageBox>
#include "app.h"
#include "serverapi.h"
#include "projectitemwdt.h"
#include "projectinfodlg.h"

Mainwnd::Mainwnd(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mainwnd)
    , scrollArea(new QScrollArea)
{
    ui->setupUi(this);
    setWindowTitle("Quwi-Test");
    m_pProjInfoDlg = new ProjectInfoDlg(this);
}

Mainwnd::~Mainwnd()
{
    delete ui;
}
void Mainwnd::loadProjects()
{
    QVBoxLayout* const listLayout = (QVBoxLayout*)ui->projectList->layout();
//    ui->projectList->setUpdatesEnabled(false);
//    qDeleteAll(ui->projectList->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
//    ui->projectList->setUpdatesEnabled(true);

    // *** load projects list from server ***
    QJsonObject resObj = g_pServerApi->getProjects();
    QJsonValue projVal = resObj.value("projects");
    QJsonArray projAry= projVal.toArray();
    foreach (const QJsonValue & v, projAry) {
        QJsonObject itemObj = v.toObject();
        ProjectItemWdt *projectItem = new ProjectItemWdt(itemObj, ui->projectList);
        connect(projectItem, SIGNAL(onClick(int)), this, SLOT(on_projectItem_clicked(int)));
        listLayout->addWidget( projectItem, 0, Qt::AlignCenter);
    }
}
void Mainwnd::showEvent(QShowEvent *event)
{
    loadProjects();
}
void Mainwnd::on_projectItem_clicked(int id)
{
    m_pProjInfoDlg->setProjectId(id);
    m_pProjInfoDlg->show();
}
void Mainwnd::on_projectsBtn_clicked()
{
}
void Mainwnd::on_logoutBtn_clicked()
{
    g_app->showLoginDlg();
}
