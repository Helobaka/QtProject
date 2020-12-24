#include "payment.h"
#include "ui_payment.h"
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

Payment::Payment(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
    ui->AddCard->hide();
    hidePay();

    score_validator = new  QRegExpValidator(QRegExp("^[1-9][0-9]*$"));

    ui->PayEdit->setValidator(score_validator);
}

Payment::~Payment(){
    delete ui;
}


void Payment::confirmation(QSqlTableModel *model, QString  UserID, QString FriendID){

    QJsonObject operationObj;
    operationObj.insert("type", "doPayment");
    operationObj.insert("friend_id", FriendID);
    operationObj.insert("user_id", UserID);

    QJsonDocument operationDoc;
    operationDoc.setObject(operationObj);

    sgnDoPayment(operationDoc);



    this->model = model;

    QString Phone = model->record(0).value("phone").toString();
    this->Login = model->record(0).value("login").toString();

    this->model->setTable("cards");
    QString filter = QString("login='%1'").arg(this->Login);
    this->model->setFilter(filter);
    this->model->select();

    this->cardNumber = model->record(0).value("number").toString();

    if(model->rowCount() >= 1){
        ui->CardLabel->setText("Номер карты: " + this->cardNumber);
        showPay();
    }else{
        ui->CardLabel->setText("Номер карты: у вас не привязана карта");
        ui->AddCard->show();
        hidePay();
    }

    this->model = model;
    this->model->setTable("people");
    filter = QString("user_id='%1'").arg(FriendID);
    this->model->setFilter(filter);
    this->model->select();
    Phone = model->record(0).value("phone").toString();
    this->userId = UserID;
    this->friendId = FriendID;
    ui->PhoneLabel->setText("Номер телефона получателя: " + Phone);
}

void Payment::sltDoPaymentResult(QJsonObject result){

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
    this->cardNumber = bankCardRecord.value("number").toString();
    ui->CardLabel->setText("Номер карты: " + this->cardNumber);
    ui->AddCard->hide();
    showPay();
    this->show();
}

void  Payment::callBackCancel()
{
    this->show();
}

void Payment::hidePay()
{
    ui->PayEdit->hide();
    ui->PayLabel->hide();
    ui->PayButton->hide();
}

void Payment::showPay()
{
    ui->PayEdit->show();
    ui->PayLabel->show();
    ui->PayButton->show();
}

void Payment::on_PayButton_clicked()
{
    QString Score = ui->PayEdit->text();
    int pos = 0;

    if(score_validator->validate(Score,pos) != QValidator::Acceptable)
    {
        ui->PayErrorLabel->setText("*Некорректное значение");
    }
    else
    {
       model->setTable("operations");
       QSqlRecord operationRecord = model->record();
       operationRecord.remove(operationRecord.indexOf("operation_id"));

       QString datetime = QDateTime::currentDateTime().toString();

       QJsonObject operationObj;
       operationObj.insert("user_id", this->userId);
       operationObj.insert("price", Score);
       operationObj.insert("card_number", this->cardNumber);
       operationObj.insert("datetime", datetime);

       QJsonDocument operationDoc;
       operationDoc.setObject(operationObj);

       operationRecord.setValue("user_id", userId);
       operationRecord.setValue("json", QString::fromStdString(operationDoc.toJson(QJsonDocument::Compact).toStdString()));

       if(this->model->insertRecord(-1, operationRecord))
       {

           //Пополнение своего баланса

           this->model->setTable("people");
           QString filter = QString("user_id = '%1'").arg(friendId);
           this->model->setFilter(filter);
           this->model->select();

           QSqlRecord updateRecord =  this->model->record(0);

           int oldScore = updateRecord.value("score").toInt();
           QString newScore = QString::number(Score.toInt() + oldScore);

           updateRecord.setValue("score", newScore);

           this->model->setRecord(0, updateRecord);

           if (this->model->submitAll())
           {
               if(friendId!=userId)
               emit backPayment("");
               else
               emit backPayment(newScore);
               this->close();
           }
       }

    }
}

void Payment::on_CancelButton_clicked()
{
    emit cancelPayment();
    this->close();
}
