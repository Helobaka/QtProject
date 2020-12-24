#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

class TcpClient: public QObject
{
    Q_OBJECT
public:
    TcpClient();
    ~TcpClient();

    QTcpSocket* socket;
    QByteArray data;
    QJsonDocument doc;
    QJsonParseError docError;
public slots:
    void sockReady();
    void sockDisc();
    void sltAuthentication(QString login, QString password);
    void sltAddPeople(QJsonDocument);
    void sltAddCard(QJsonDocument);
    void sltGetPeople(QJsonDocument);
    void sltDoPayment(QJsonDocument);
    //void sgnPayResult(QJsonDocument);
    void sltPay(QJsonDocument doc);
    void sltAddFriend(QJsonDocument doc);

signals:
    void sgnAuthenticationResult(bool);
    void sgnAddPeopleResult(bool);
    void sgnGetPeopleResult(QJsonObject);
    void sgnDoPaymentResult(QJsonObject);
    //void sltPay(QJsonDocument doc);
    void sgnPayResult(QJsonObject);
    void sgnAddFriendResult(QJsonObject);

};

#endif // TCPCLIENT_H
