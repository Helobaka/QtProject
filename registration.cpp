#include "registration.h"
#include "ui_registration.h"
#include "databasepsql.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>


Registration::Registration(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    phone_validator = new QRegExpValidator(QRegExp("^\\+\\d{11}$"));
    name_validator = new QRegExpValidator(QRegExp("^[A-Za-z]{3,25}$"));
    surname_validator = new QRegExpValidator(QRegExp("^[A-Za-z]{3,25}$"));
    patronymic_validator = new QRegExpValidator(QRegExp("^[A-Za-z]{3,25}$"));
    login_validator = new QRegExpValidator(QRegExp("^[A-Za-z]{1}[A-Za-z0-9]{5,25}$"));
    password_validator = new QRegExpValidator(QRegExp("^[A-Za-z0-9]{8,25}$"));


    ui->Phone->setValidator(phone_validator);
    ui->Login->setValidator(login_validator);
    ui->Password->setValidator(password_validator);
    ui->Name->setValidator(name_validator);
    ui->Patronymic->setValidator(patronymic_validator);
    ui->Surname->setValidator(surname_validator);

    ui->checkCard->hide();
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_callBack_clicked()
{
    emit callBackRegistration();
    this->close();
}

void Registration::on_register_2_clicked()
{
    QMessageBox msgBox;

    int pos = 0;
    bool isValid = true;

    DataBasePSQL* dbSingle = DataBasePSQL::Instance();
    QSqlDatabase db = dbSingle->getDB();
    QSqlTableModel* model = new QSqlTableModel(this, db);

    QString Login = ui->Login->text();
    QString Password = ui->Password->text();
    QString ConfirmPassword = ui->ConfirmPassword->text();
    QString Name = ui->Name->text();
    QString Surname = ui->Surname->text();
    QString Patronymic = ui->Patronymic->text();
    QString Phone = ui->Phone->text();

    QString filter = QString("login='%1'").arg(Login);
    model->setTable("people");
    QSqlRecord newRecord=model->record();
    model->setFilter(filter);
    model->select();

    if(model->rowCount()==1){
        ui->ErrorLogin->setText("*Такой логин существует");
        isValid=false;
    }else{
        if(login_validator->validate(Login, pos) != QValidator::Acceptable){
            ui->ErrorLogin->setText("*Некорректный логин");
            isValid=false;
        }else{
            ui->ErrorLogin->setText("");
        }
    }

    if(password_validator->validate(Password, pos) != QValidator::Acceptable){
        ui->ErrorPassword->setText("*Некорректный пароль");
        isValid=false;
    }else{
        ui->ErrorPassword->setText("");
    }

    if(Password!=ConfirmPassword){
        ui->ErrorConfirmPassword->setText("*Пароли не совпадают");
        isValid=false;
    }else{
        ui->ErrorConfirmPassword->setText("");
    }

    if(name_validator->validate(Name, pos) != QValidator::Acceptable){
        ui->ErrorName->setText("*Введите имя");
        isValid=false;
    }else{
        ui->ErrorName->setText("");
    }

    if(surname_validator->validate(Surname, pos) != QValidator::Acceptable){
        ui->ErrorSurname->setText("*Введите фамилию");
        isValid=false;
    }else{
        ui->ErrorSurname->setText("");
    }

    if(patronymic_validator->validate(Patronymic, pos) != QValidator::Acceptable){
        ui->ErrorPatronymic->setText("*Введите отчество");
        isValid=false;
    }else{
        ui->ErrorPatronymic->setText("");
    }

    if(phone_validator->validate(Phone, pos) != QValidator::Acceptable){
        ui->ErrorPhone->setText("*Некорректный номер");
        isValid=false;
    }else{
        ui->ErrorPhone->setText("");
    }


    if(isValid){
        newRecord.setValue("login", Login);
        newRecord.setValue("password", Password);
        newRecord.setValue("name", Name);
        newRecord.setValue("surname", Surname);
        newRecord.setValue("patronymic", Patronymic);
        newRecord.setValue("phone", Phone);

        model->insertRecord(-1,newRecord);

        if(model->submitAll()){
            msgBox.setText("Вы зарегистрировались!");
            msgBox.exec();
            if(ui->checkCard->isChecked()){
                bankCardRecord.setValue("login", Login);
                bankCardRecord.remove(bankCardRecord.indexOf("id_card"));
                model->setTable("cards");
                model->insertRecord(-1, bankCardRecord);
                model->submitAll();
            }
            emit callBackRegistration();
            this->close();
        }else{
            msgBox.setText("Ошибка!");
            msgBox.exec();
        }    
    }

}

void Registration::on_AddCard_clicked()
{
    this->hide();
    this->bankCard = new BankCard();
    connect(bankCard, SIGNAL(callBackBankCard(QSqlRecord)), this, SLOT(callBackBankCard(QSqlRecord)));
    connect(bankCard, SIGNAL(callBackCancel()), this, SLOT(callBackCancel()));
    bankCard->show();
}


void Registration::callBackBankCard(QSqlRecord Record)
{
    bankCardRecord = Record;
    ui->checkCard->setChecked(true);

    bankCardRecord.value("number");

    ui->CardNumber->setText(bankCardRecord.value("number").toString().left(4).insert(4,"XXXXXXXXXXXX"));

    ui->checkCard->show();
    this->show();

//    DataBasePSQL* dbSingle = DataBasePSQL::Instance();
//    QSqlDatabase db = dbSingle->getDB();
//    QSqlTableModel* model = new QSqlTableModel(this, db);

//    Record.setValue("login", "qwerty");
//    model->setTable("cards");
//    model->insertRecord(-1, Record);
//    model->submitAll();
}

void  Registration::callBackCancel()
{
    ui->checkCard->setChecked(false);
    ui->CardNumber->setText("");
    this->show();
}
