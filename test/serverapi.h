#ifndef SERVERAPI_H
#define SERVERAPI_H

#include <QObject>
#include <QNetworkAccessManager>

class ServerApi : public QObject
{
    Q_OBJECT
public:
    explicit ServerApi(QObject *parent = nullptr);

    QJsonObject login(QString &email, QString &password);
    QJsonObject getProjects();
    QJsonObject getProject(int id);
    QJsonObject updateProject(int id, QUrlQuery &query);
    QPixmap downloadImage(QString &path);

protected:
    QByteArray postRequest(QUrl &reqUrl, QByteArray &reqData, QString headerType="application/json");
    QByteArray getRequest(QUrl &reqUrl);

public:
    static QJsonObject ByteAry2JsonObj(QByteArray &ary);
    static QByteArray JsonObj2ByteAry(QJsonObject &obj);

protected:
    QNetworkAccessManager *manager;
    QString m_apiBaseURL;
    QString m_email, m_password;
    QString m_token;
};
extern ServerApi *g_pServerApi;

#endif // SERVERAPI_H
