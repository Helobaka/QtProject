#include "tcpclient.h"
#include "databasepsql.h"
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QSqlError>

TcpClient::TcpClient()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this,  SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this,  SLOT(sockDisc()));
    socket->connectToHost("127.0.0.1", 10000);
}

TcpClient::~TcpClient()
{

}

void TcpClient::sockDisc(){
    socket->deleteLater();
}

void  TcpClient::sockReady(){
//    if(socket->waitForConnected(500)){
//        socket->waitForReadyRead(500);
        data = socket->readAll();
        //qDebug() << "prihlo 4toto";
        qDebug() << data;
        doc = QJsonDocument::fromJson(data, &docError);
        QJsonObject operation = doc.object();
        if(operation["type"].toString() == "selectAuth"){
            sgnAuthenticationResult(operation["result"].toBool());
        }else  if(operation["type"].toString() == "addPeople"){
            sgnAddPeopleResult(operation["result"].toBool());
        }else  if(operation["type"].toString() == "getPeople"){
            sgnGetPeopleResult(operation);
        }else if(operation["type"].toString() == "doPayment"){
            sgnDoPaymentResult(operation);
        }else if(operation["type"].toString() == "pay"){
            sgnPayResult(operation);
        }else if(operation["type"].toString() == "addFriend"){
            sgnAddFriendResult(operation);
        }else   if(data.count()  >  0){
            sockReady();
        }
//    }
}

void TcpClient::sltAuthentication(QString login, QString password){
    QJsonObject operationObj;
    operationObj.insert("type", "selectAuth");
    operationObj.insert("login", login);
    operationObj.insert("password", password);

    QJsonDocument operationDoc;
    operationDoc.setObject(operationObj);
    socket->write(QString::fromStdString(operationDoc.toJson(QJsonDocument::Compact).toStdString()).toUtf8());
}

void TcpClient::sltAddPeople(QJsonDocument doc){
    socket->write(QString::fromStdString(doc.toJson(QJsonDocument::Compact).toStdString()).toUtf8());
}

void TcpClient::sltAddCard(QJsonDocument doc){
    socket->write(QString::fromStdString(doc.toJson(QJsonDocument::Compact).toStdString()).toUtf8());
}

void TcpClient::sltGetPeople(QJsonDocument doc){
    socket->write(QString::fromStdString(doc.toJson(QJsonDocument::Compact).toStdString()).toUtf8());
}

void TcpClient::sltDoPayment(QJsonDocument doc){
    socket->write(QString::fromStdString(doc.toJson(QJsonDocument::Compact).toStdString()).toUtf8());
}

void TcpClient::sltPay(QJsonDocument doc){
    socket->write(QString::fromStdString(doc.toJson(QJsonDocument::Compact).toStdString()).toUtf8());
}

void TcpClient::sltAddFriend(QJsonDocument doc){
    socket->write(QString::fromStdString(doc.toJson(QJsonDocument::Compact).toStdString()).toUtf8());
}
