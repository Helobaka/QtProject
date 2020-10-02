#ifndef BANKCARD_H
#define BANKCARD_H

#include <QWidget>
#include <QSqlRecord>
#include <QRegExpValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class BankCard; }
QT_END_NAMESPACE

class BankCard: public QWidget{
    Q_OBJECT

public:
    explicit BankCard(QWidget *parent=0);
    ~BankCard();

signals:
    void callBackBankCard(QSqlRecord Record);
    void callBackCancel();

private slots:
    void on_AddCard_clicked();

    void on_Cancel_clicked();

private:
    Ui::BankCard *ui;
    QRegExpValidator  *name_validator, *surname_validator, *number_validator, *month_validator, *year_validator, *cvv_validator;

};

#endif // BANKCARD_H
