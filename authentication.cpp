#include "authentication.h"
#include "ui_authentication.h"
#include "databasepsql.h"
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QDebug>
#include <QTableView>
#include <QSqlRecord>


Authentication::Authentication(QWidget *parent):
        QWidget(parent),
        ui(new Ui::Authentication)
{
     ui->setupUi(this);
     client = new TcpClient();
     mainWindow = new MainWindow();
     connect(this, SIGNAL(sendLogin(QString)), mainWindow, SLOT(getLogin(QString)));
     connect(this, SIGNAL(sgnAuthentication(QString, QString)), client, SLOT(sltAuthentication(QString, QString)));
     connect(client, SIGNAL(sgnAuthenticationResult(bool)), this, SLOT(sltAuthenticationResult(bool)));
     //client->sltAuthentication("QString login");
//     connect(client, SIGNAL(sgnGetPeopleResult(QJsonObject)), mainWindow, SLOT(sltGetPeopleResult(QJsonObject)));
//     connect(mainWindow, SIGNAL(sgnGetPeople(QJsonDocument)), client, SLOT(sltGetPeople(QJsonDocument)));
}

Authentication::~Authentication()
{
    delete ui;
}

void Authentication::on_BtnLogin_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(" ");

    sgnAuthentication(ui->TextLogin->text(), ui->TextPassword->text());
}

void Authentication::on_Registration_clicked()
{
    hide();
    registration = new Registration();
    connect(registration, SIGNAL(callBackRegistration()), this, SLOT(callBackRegistration()));
    connect(registration, SIGNAL(sgnAddPeople(QJsonDocument)), client, SLOT(sltAddPeople(QJsonDocument)));
    connect(registration, SIGNAL(sgnAddCard(QJsonDocument)), client, SLOT(sltAddCard(QJsonDocument)));
    connect(client, SIGNAL(sgnAddPeopleResult(bool)), registration, SLOT(sltAddPeopleResult(bool)));
    //connect(registration, SIGNAL(sgnAddCard(QJsonDocument)), client, SLOT(sltAddCard(QJsonDocument)));
    registration->show();
    registration->client = client;
}

void Authentication::callBackRegistration(){
    show();
}


void Authentication::sltAuthenticationResult(bool result){
    QMessageBox msgBox;
    msgBox.setWindowTitle(" ");
    if(!result){
        msgBox.setText("Неправильный логин или пароль");
        msgBox.exec();
    }else{
        msgBox.setText("Проходите");
//        connect(client, SIGNAL(sgnGetPeopleResult(QJsonObject)), mainWindow, SLOT(sltGetPeopleResult(QJsonObject)));
//        connect(mainWindow, SIGNAL(sgnGetPeople(QJsonDocument)), client, SLOT(sltGetPeople(QJsonDocument)));
        mainWindow->setClient(client);
        mainWindow->show();
        emit sendLogin(ui->TextLogin->text());
        this->close();
    }
    //msgBox.exec();
}

