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
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_callBack_clicked()
{
    this->callBack();
    this->close();
}

void Registration::on_register_2_clicked()
{
    QMessageBox msgBox;

    DataBasePSQL* dbSingle = DataBasePSQL::Instance();
    QSqlDatabase db = dbSingle->getDB();
    QSqlTableModel* model = new QSqlTableModel(this, db);

    QString Login = ui->Login->text();

    QString filter = QString("login='%1'").arg(Login);
    model->setTable("people");
    QSqlRecord newRecord=model->record();
    model->setFilter(filter);
    model->select();

    if(model->rowCount()==1){
        msgBox.setText("Такой логин существует");
        msgBox.exec();
        return;
    }


    QString Password = ui->Password->text();
    QString ConfirmPassword = ui->ConfirmPassword->text();

    if(Password!=ConfirmPassword){
        msgBox.setText("Пароли не совпадают");
        msgBox.exec();
        return;
    }

    QString Name = ui->Name->text();
    QString Surname = ui->Surname->text();
    QString Patronymic = ui->Patronymic->text();

    newRecord.setValue("login", Login);
    newRecord.setValue("password", Password);
    newRecord.setValue("name", Name);
    newRecord.setValue("surname", Surname);
    newRecord.setValue("patronymic", Patronymic);

    model->insertRecord(-1,newRecord);
    if(model->submitAll()){
        msgBox.setText("Вы зарегистрировались!");
    }else{
        msgBox.setText("Ошибка!");
    }
    msgBox.exec();

}
