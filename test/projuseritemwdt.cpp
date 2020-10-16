#include "projuseritemwdt.h"
#include "ui_projuseritemwdt.h"
#include "serverapi.h"

ProjUserItemWdt::ProjUserItemWdt(QJsonObject obj, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjUserItemWdt)
{
    ui->setupUi(this);
    itemObj = obj;
}

ProjUserItemWdt::~ProjUserItemWdt()
{
    delete ui;
}
void ProjUserItemWdt::showEvent(QShowEvent *event)
{
    QString name = itemObj.value("name").toString();
    QString avatarUrl = itemObj.value("avatar_url").toString();
    int isOnline = itemObj.value("is_online").toInt();
    QImage avatarImage = g_pServerApi->downloadImage(avatarUrl).toImage();
    ui->avatarWdt->setUseThemeColors(true);
    ui->avatarWdt->drawOnline(true);
    ui->avatarWdt->setOnline(isOnline);
    ui->avatarWdt->setSize(32);
    QColor avatarColor(isOnline ? "#00aa00":"#aa0000");
    ui->avatarWdt->setBackgroundColor(avatarColor);
    ui->avatarWdt->setImage(avatarImage);
    if (avatarImage.isNull()) {
        ui->avatarWdt->setLetter(name[0].toUpper());
    }
    ui->nameLbl->setText(name);
}
