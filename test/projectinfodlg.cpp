#include "projectinfodlg.h"
#include "ui_projectinfodlg.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QUrlQuery>
#include <QImage>
#include <QMessageBox>
#include "serverapi.h"
#include "projuseritemwdt.h"

ProjectInfoDlg::ProjectInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectInfoDlg)
{
    setWindowTitle("Project");
    ui->setupUi(this);

    ui->okBtn->setBackgroundColor(QColor("#3a5378"));
    ui->okBtn->setFontSize(12.00);
    ui->okBtn->setHaloVisible(false);
    ui->activeToggle->setActiveColor(QColor("#00aa00"));
    ui->watcherToggle->setActiveColor(QColor("#00aa00"));
    ui->logoWdt->setSize(100);
}

ProjectInfoDlg::~ProjectInfoDlg()
{
    delete ui;
}
void ProjectInfoDlg::setProjectId(int id) {
    m_projId = id;
}
void ProjectInfoDlg::showEvent(QShowEvent *event)
{
    QJsonObject resObj = g_pServerApi->getProject(m_projId);
    QJsonValue val = resObj.value("project");
    QJsonObject itemObj = val.toObject();

    QString logoUrl = itemObj.value("logo_url").toString();
    QImage logoImage = g_pServerApi->downloadImage(logoUrl).toImage();
    ui->logoWdt->setImage(logoImage);
    QString name = itemObj.value("name").toString();
    ui->nameEdt->setText(name);
    int isActive = itemObj.value("is_active").toInt();
    ui->activeToggle->setChecked(isActive);
    int isWatcher = itemObj.value("is_owner_watcher").toInt();
    ui->watcherToggle->setChecked(isWatcher);

    QJsonValue usersVal = itemObj.value("users");
    QJsonArray userAry= usersVal.toArray();
    QHBoxLayout* const userListLayout = (QHBoxLayout*)ui->userLstWdt->layout();
    foreach (const QJsonValue & v, userAry) {
        QJsonObject itemObj = v.toObject();
        QWidget *pUserWidget = new QWidget;
        ProjUserItemWdt *userItem = new ProjUserItemWdt(itemObj, ui->userLstWdt);
        userListLayout->addWidget( userItem, 0, Qt::AlignLeft);
    }
//    QSpacerItem *pSpacerItem = new QSpacerItem(5, 0);
    userListLayout->addSpacing(1);
}
void ProjectInfoDlg::on_okBtn_clicked()
{
    QString name = ui->nameEdt->text();
    QUrlQuery reqData;
    reqData.addQueryItem("name", name);
    QJsonObject resObj = g_pServerApi->updateProject(m_projId, reqData);
    qDebug() << "updateProject:" << resObj;
    QMessageBox msgBox;
    msgBox.setText("The name of project is updated.");
    msgBox.exec();

}
