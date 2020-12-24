#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "bankcard.h"
#include <QWidget>
#include <QValidator>
#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Registration; }
QT_END_NAMESPACE

class Registration:  public QWidget{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent=0);
    ~Registration();
    TcpClient* client;

signals:
    void callBackRegistration();
    void sgnAddPeople(QJsonDocument);
    void sgnAddCard(QJsonDocument);

private slots:
    void on_callBack_clicked();

    void on_register_2_clicked();

    void on_AddCard_clicked();

    void callBackBankCard(QJsonObject Record);

    void callBackCancel();

    void sltAddPeopleResult(bool);

private:
    Ui::Registration *ui;
    QRegExpValidator *phone_validator, *login_validator, *name_validator, *surname_validator, *patronymic_validator, *password_validator;
    BankCard* bankCard;
    QJsonObject bankCardRecord;
};

#endif // REGISTRATION_H
