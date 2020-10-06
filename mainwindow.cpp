#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "databasepsql.h"
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    payment = new Payment();
    connect(this, SIGNAL(confirmation(QSqlTableModel*)), payment, SLOT(confirmation(QSqlTableModel*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getLogin(QString Login){
    this->Login = Login;

    DataBasePSQL* dbSingle = DataBasePSQL::Instance();
    QSqlDatabase db = dbSingle->getDB();
    this->model = new QSqlTableModel(this, db);

    this->model->setTable("people");
    QString filter = QString("login='%1'").arg(this->Login);
    this->model->setFilter(filter);
    this->model->select();

    QString Name = this->model->record(0).value("name").toString();
    QString Surname = this->model->record(0).value("surname").toString();
    QString Patronymic = this->model->record(0).value("patronymic").toString();
    QString Score = this->model->record(0).value("score").toString();
    QString Phone = this->model->record(0).value("phone").toString();

    ui->NameLabel->setText("Здравствуйте! " + Surname + " " + Name + " " + Patronymic);
    ui->ScoreLabel->setText("Ваш баланс: " + Score);
    ui->PhoneLabel->setText("Ваш номер: " + Phone);
}


void MainWindow::on_payConfirm_clicked()
{
    this->hide();
    emit confirmation(this->model);
    payment->show();
}
