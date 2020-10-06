#include "payment.h"
#include "ui_payment.h"
#include <QSqlRelationalTableModel>
#include <QSqlRecord>

Payment::Payment(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
    ui->AddCard->hide();
}

Payment::~Payment(){
    delete ui;
}


void Payment::confirmation(QSqlTableModel *model){
    this->model = model;

    QString Phone = model->record(0).value("phone").toString();
    this->Login = model->record(0).value("login").toString();
    QString userId = model->record(0).value("user_id").toString();

    ui->PhoneLabel->setText("Номер телефона: " + Phone);

    this->model->setTable("cards");
    QString filter = QString("login='%1'").arg(this->Login);
    this->model->setFilter(filter);
    this->model->select();

    QString cardNumber = model->record(0).value("number").toString();

    if(model->rowCount() >= 1){
        ui->CardLabel->setText("Номер карты: " + cardNumber);
    }else{
        ui->CardLabel->setText("Номер карты: у вас не привязана карта");
        ui->AddCard->show();
    }
}

void Payment::on_AddCard_clicked()
{
    this->hide();
    this->bankCard = new BankCard();
    connect(bankCard, SIGNAL(callBackBankCard(QSqlRecord)), this, SLOT(callBackBankCard(QSqlRecord)));
    connect(bankCard, SIGNAL(callBackCancel()), this, SLOT(callBackCancel()));
    bankCard->show();
}

void Payment::callBackBankCard(QSqlRecord Record)
{
    bankCardRecord = Record;
    bankCardRecord.setValue("login", this->Login);
    bankCardRecord.remove(bankCardRecord.indexOf("id_card"));
    model->setTable("cards");
    model->insertRecord(-1, bankCardRecord);
    model->submitAll();
    ui->CardLabel->setText("Номер карты: " + bankCardRecord.value("number").toString());
    ui->AddCard->hide();
    this->show();
}

void  Payment::callBackCancel()
{
    this->show();
}
