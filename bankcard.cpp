#include "bankcard.h"
#include "ui_bankcard.h"
#include "databasepsql.h"


BankCard::BankCard(QWidget *parent):
    QWidget(parent),
    ui(new Ui::BankCard)
{
    ui->setupUi(this);
}

BankCard::~BankCard()
{
    delete ui;
}

void BankCard::on_AddCard_clicked()
{
    DataBasePSQL* dbSingle = DataBasePSQL::Instance();
    QSqlDatabase db = dbSingle->getDB();
    QSqlTableModel* model = new QSqlTableModel(this, db);

    model->setTable("cards");


    QString Name = ui->Name->text();
    QString Surname = ui->Surname->text();
    QString Number = ui->Number->text();
    QString Month = ui->Month->text();
    QString Year = ui->Year->text();
    QString CVV = ui->CVV->text();

    QSqlRecord newRecord = model->record();

    newRecord.setValue("month", Month);
    newRecord.setValue("number", Number);
    newRecord.setValue("name", Name);
    newRecord.setValue("surname", Surname);
    newRecord.setValue("year", Year);
    newRecord.setValue("cvv", CVV);

    emit callBackBankCard(newRecord);
}
