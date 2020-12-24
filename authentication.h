#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "mainwindow.h"
#include "registration.h"
#include "tcpclient.h"
#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

QT_BEGIN_NAMESPACE
namespace Ui { class Authentication; }
QT_END_NAMESPACE

class Authentication :  public QWidget{
    Q_OBJECT

public:
    explicit Authentication(QWidget *parent=0);
    ~Authentication();
    TcpClient* client;

signals:
    void sendLogin(QString Login);
    void sgnAuthentication(QString, QString);

private slots:

    void callBackRegistration();

    void on_BtnLogin_clicked();

    void on_Registration_clicked();

    void sltAuthenticationResult(bool);

private:
    Ui::Authentication *ui;
    MainWindow *mainWindow;
    Registration* registration;
};


#endif // AUTHENTICATION_H
