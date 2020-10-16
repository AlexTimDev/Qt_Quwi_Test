#include "projectitemwdt.h"
#include "ui_projectitemwdt.h"
#include <QDebug>
#include "serverapi.h"

ProjectItemWdt::ProjectItemWdt(QJsonObject obj, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectItemWdt)
{
    ui->setupUi(this);
    setMouseTracking(true);
    itemObj = obj;
}

ProjectItemWdt::~ProjectItemWdt()
{
    delete ui;
}
int ProjectItemWdt::getId()
{
    int id = itemObj.value("id").toInt();
    return id;
}
void ProjectItemWdt::setName(QString name)
{
    ui->nameLbl->setText(name);
}
void ProjectItemWdt::showEvent(QShowEvent *event)
{
    QString logoUrl = itemObj.value("logo_url").toString();
    QPixmap logoImage = g_pServerApi->downloadImage(logoUrl);
    ui->logoLbl->setPixmap(logoImage);
    QString name = itemObj.value("name").toString();
    setName(name);
    int isActive = itemObj.value("is_active").toInt();
    ui->stateLbl->setText(isActive==1 ? "Active": "Inactive");
    if (!isActive) ui->stateLbl->setStyleSheet("QLabel { color : darkred; font-size: 18px; }");
}
void ProjectItemWdt::mouseMoveEvent(QMouseEvent *event)
{
    setCursor(Qt::PointingHandCursor);
}
void ProjectItemWdt::mouseReleaseEvent(QMouseEvent *event)
{
    int id = itemObj.value("id").toInt();
    emit(onClick(id));
}
