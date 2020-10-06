#ifndef PAYMENT_H
#define PAYMENT_H

#include "bankcard.h"
#include <QSqlRelationalTableModel>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Payment; }
QT_END_NAMESPACE

class Payment: public QWidget{
    Q_OBJECT

public:
    explicit Payment(QWidget *parent = 0);
    ~Payment();

private slots:

    void confirmation(QSqlTableModel *model);

    void callBackBankCard(QSqlRecord Record);

    void callBackCancel();

    void on_AddCard_clicked();

private:
    Ui::Payment *ui;
    QSqlTableModel *model;
    BankCard *bankCard;
    QSqlRecord bankCardRecord;
    QString Login;
};

#endif // PAYMENT_H
