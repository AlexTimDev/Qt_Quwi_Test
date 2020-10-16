#include "logindlg.h"
#include "ui_logindlg.h"
#include "serverapi.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);

    ui->loginBtn->setBackgroundColor(QColor("#3a5378"));
    ui->loginBtn->setFontSize(12.00);
    ui->loginBtn->setHaloVisible(false);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginBtn_clicked()
{
    QString strEmail = ui->emailEdt->text();
    QString strPassword = ui->passwordEdt->text();

    ui->loginBtn->setText("Logining...");
    ui->loginBtn->setDisabled(true);
    QJsonObject resObj = g_pServerApi->login(strEmail, strPassword);
    ui->loginBtn->setText("Login");
    ui->loginBtn->setDisabled(false);

    QJsonValue tokenValue = resObj.value("token");

    if (tokenValue.isNull() || tokenValue.isUndefined()) {
        QMessageBox msgBox(QMessageBox::Warning, "Warning", "Incorrect email or password.");
        msgBox.exec();
    } else {
//        QMessageBox msgBox(QMessageBox::Information, "OK", "You are certificated.");
//        msgBox.exec();
        accept();
    }
}
