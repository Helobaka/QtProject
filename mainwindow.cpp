#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "databasepsql.h"
#include "authentication.h"
#include <QSqlRecord>
#include <QJsonDocument>
#include <QJsonObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    payment = new Payment();
    connect(this, SIGNAL(confirmation(QSqlTableModel*)), payment, SLOT(confirmation(QSqlTableModel*)));
    connect(payment, SIGNAL(backPayment(QString)), this, SLOT(backPayment(QString)));
    connect(payment, SIGNAL(cancelPayment()), this, SLOT(cancelPayment()));
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

    userID = this->model->record(0).value("user_id").toString();

    QString Name = this->model->record(0).value("name").toString();
    QString Surname = this->model->record(0).value("surname").toString();
    QString Patronymic = this->model->record(0).value("patronymic").toString();
    QString Score = this->model->record(0).value("score").toString();
    QString Phone = this->model->record(0).value("phone").toString();

    ui->NameLabel->setText("Здравствуйте! " + Surname + " " + Name + " " + Patronymic);
    ui->ScoreLabel->setText("Ваш баланс: " + Score);
    ui->PhoneLabel->setText("Ваш номер: " + Phone);

    this->viewOperations();

}

void MainWindow::viewOperations(){
    this->model->setTable("operations");
    QString filter = QString("user_id='%1'").arg(this->userID);
    this->model->setFilter(filter);
    this->model->select();

    viewModel = new QStandardItemModel();
    int rowCount = model->rowCount();
//    int columnCount = model->record().count() - 1 ;
    viewModel->setRowCount(rowCount);
    viewModel->setColumnCount(4);

    QStringList headers = QStringList() << "user_id" << "price" << "card_number" << "datetime";
    viewModel->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < rowCount; i++){
        QJsonObject operation = QJsonDocument().fromJson(model->record(i).value("json").toByteArray()).object();
        viewModel->setItem(i, 0, new QStandardItem(operation["user_id"].toString()));
        viewModel->setItem(i, 1, new QStandardItem(operation["price"].toString()));
        viewModel->setItem(i, 2, new QStandardItem(operation["card_number"].toString()));
        viewModel->setItem(i, 3, new QStandardItem(operation["datetime"].toString()));
    }

    ui->tableView->setModel(viewModel);
}

void MainWindow::on_payConfirm_clicked()
{
    this->hide();
    this->model->setTable("people");
    QString filter = QString("login='%1'").arg(this->Login);
    this->model->setFilter(filter);
    this->model->select();
    emit confirmation(this->model);
    payment->show();
}

void MainWindow::backPayment(QString newScore){
    ui->ScoreLabel->setText("Ваш баланс: " + newScore);
    viewOperations();
    this->show();
}

void MainWindow::cancelPayment(){
    this->show();
}

void MainWindow::on_ExitButton_clicked()
{
    Authentication *w = new Authentication();
    w->show();
    this->close();
}
