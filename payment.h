#ifndef PAYMENT_H
#define PAYMENT_H

#include "bankcard.h"
#include <QSqlRelationalTableModel>
#include <QWidget>
#include <QValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class Payment; }
QT_END_NAMESPACE

class Payment: public QWidget{
    Q_OBJECT

public:
    explicit Payment(QWidget *parent = 0);
    ~Payment();

private slots:

    //void confirmation(QSqlTableModel *model);
    void confirmation(QSqlTableModel *model, QString  UserID, QString FriendID);

    void callBackBankCard(QSqlRecord Record);

    void callBackCancel();

    void on_AddCard_clicked();

    void on_PayButton_clicked();

    void on_CancelButton_clicked();

signals:
    void on_payConfirm_clicked();

    void backPayment(QString newScore);

    void cancelPayment();

    void sgnDoPayment(QJsonDocument);

private:
    Ui::Payment *ui;
    QSqlTableModel *model;
    BankCard *bankCard;
    QSqlRecord bankCardRecord;
    QString Login;
    QString userId;
    QString friendId;
    QString cardNumber;
    QRegExpValidator *score_validator;

    void hidePay();
    void showPay();
};

#endif // PAYMENT_H
