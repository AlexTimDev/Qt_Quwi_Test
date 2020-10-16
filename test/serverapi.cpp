#include "serverapi.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QByteArray>
#include <QMessageBox>
#include <QTimer>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QEventLoop>

ServerApi *g_pServerApi;
ServerApi::ServerApi(QObject *parent) : QObject(parent)
{
    // *** initialize member *** //
    g_pServerApi = this;
    m_apiBaseURL = "https://api.quwi.com/v2/";

    manager = new QNetworkAccessManager(this);
}
QJsonObject ServerApi::login(QString &email, QString &password) {
    m_email = email;
    m_password = password;

    QUrl url(m_apiBaseURL+"auth/login?");

    QJsonObject login;

    login["email"] = email;
    login["password"] = password;

    QByteArray reqData = JsonObj2ByteAry(login);
    QByteArray resData = postRequest(url, reqData);
    QJsonObject resObj = ByteAry2JsonObj(resData);
    QJsonValue tokenValue = resObj.value("token");
    m_token = "Bearer " + tokenValue.toString();
    return resObj;
}
QJsonObject ServerApi::getProjects() {
    QUrl url(m_apiBaseURL+"projects-manage/index");
    QByteArray data = getRequest(url);
    return ByteAry2JsonObj(data);
}
QJsonObject ServerApi::getProject(int id) {
    QString uri = "projects-manage/"+QString("%1").arg(id);
    QUrl url(m_apiBaseURL+uri);
    QByteArray data = getRequest(url);
    return ByteAry2JsonObj(data);
}
QJsonObject ServerApi::updateProject(int id, QUrlQuery &query) {
    QString uri = "projects-manage/update?id="+QString("%1").arg(id);
    QUrl url(m_apiBaseURL+uri);
    QByteArray reqData = query.toString(QUrl::FullyEncoded).toUtf8();
    QByteArray resData = postRequest(url, reqData, "application/x-www-form-urlencoded");
    QJsonObject resObj = ByteAry2JsonObj(resData);
    return resObj;
}
QPixmap ServerApi::downloadImage(QString &path) {
    QUrl url(path);
    QByteArray data = getRequest(url);
    QPixmap pixmap;
    pixmap.loadFromData(data);
    return pixmap;
}
QByteArray ServerApi::postRequest(QUrl &reqUrl, QByteArray &reqData, QString headerType) {
    QNetworkRequest request(reqUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, headerType);
    request.setRawHeader("Authorization", m_token.toLocal8Bit());

    QNetworkReply *reply = manager->post(request, reqData);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray resData = reply->readAll();
    return resData;
}
QByteArray ServerApi::getRequest(QUrl &reqUrl) {
    QNetworkRequest request(reqUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", m_token.toLocal8Bit());

    QNetworkReply *reply = manager->get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray resData = reply->readAll();
    return resData;
}
QJsonObject ServerApi::ByteAry2JsonObj(QByteArray &ary)
{
    QJsonDocument doc = QJsonDocument::fromJson(ary);
    QJsonObject obj = doc.object();
    return obj;
}
QByteArray ServerApi::JsonObj2ByteAry(QJsonObject &obj)
{
    QJsonDocument doc;
    doc.setObject(obj);

    QByteArray ary;
    ary.append(doc.toJson());
    return ary;
}
