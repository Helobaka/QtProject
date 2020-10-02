#include "bankcard.h"
#include "ui_bankcard.h"
#include "databasepsql.h"


BankCard::BankCard(QWidget *parent):
    QWidget(parent),
    ui(new Ui::BankCard)
{
    ui->setupUi(this);

    name_validator = new QRegExpValidator(QRegExp("^[A-Za-z]{3,25}$"));
    number_validator = new QRegExpValidator(QRegExp("^[0-9]{16}$"));
    month_validator = new QRegExpValidator(QRegExp("^[1]{1}[0-2]{1}|[1-9]{1}$"));
    year_validator = new QRegExpValidator(QRegExp("^2{1}0{1}[0-9]{2}$"));
    surname_validator = new QRegExpValidator(QRegExp("^[A-Za-z]{3,25}$"));
    cvv_validator = new QRegExpValidator(QRegExp("^[0-9]{3}$"));

    ui->Name->setValidator(name_validator);
    ui->Month->setValidator(month_validator);
    ui->Year->setValidator(year_validator);
    ui->Surname->setValidator(surname_validator);
    ui->CVV->setValidator(cvv_validator);
    ui->Number->setValidator(number_validator);

}

BankCard::~BankCard()
{
    delete ui;
}

void BankCard::on_AddCard_clicked()
{
    bool isValid = true;
    int pos = 0;

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

    if(name_validator->validate(Name, pos) != QValidator::Acceptable){
        ui->ErrorName->setText("*Некорректное имя");
        isValid=false;
    }else{
        ui->ErrorName->setText("");
    }

    if(surname_validator->validate(Surname, pos) != QValidator::Acceptable){
        ui->ErrorSurname->setText("*Некорректная фамилия");
        isValid=false;
    }else{
        ui->ErrorSurname->setText("");
    }

    if((month_validator->validate(Month, pos) != QValidator::Acceptable) || (year_validator->validate(Year, pos) != QValidator::Acceptable)){
        ui->ErrorDate->setText("*Некорректный срок");
        isValid=false;
    }else{
        ui->ErrorDate->setText("");
    }

    if(number_validator->validate(Number, pos) != QValidator::Acceptable){
        ui->ErrorNumber->setText("*Некорректный номер карты");
        isValid=false;
    }else{
        ui->ErrorNumber->setText("");
    }

    if(cvv_validator->validate(CVV, pos) != QValidator::Acceptable){
        ui->ErrorCVV->setText("*Некорректное значение");
        isValid=false;
    }else{
        ui->ErrorCVV->setText("");
    }

    if(isValid){
        QSqlRecord newRecord = model->record();

        newRecord.setValue("month", Month);
        newRecord.setValue("number", Number);
        newRecord.setValue("name", Name);
        newRecord.setValue("surname", Surname);
        newRecord.setValue("year", Year);
        newRecord.setValue("cvv", CVV);

        emit callBackBankCard(newRecord);
        this->close();
    }
}

void BankCard::on_Cancel_clicked()
{
    emit callBackCancel();
    this->close();
}
