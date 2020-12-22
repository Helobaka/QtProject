#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "databasepsql.h"
#include "authentication.h"
#include <QSqlRecord>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    phone_validator = new QRegExpValidator(QRegExp("^\\+\\d{11}$"));
    name_validator = new QRegExpValidator(QRegExp("^[A-Za-z]{3,25}$"));

    ui->friendName->setValidator(name_validator);
    ui->friendPhone->setValidator(phone_validator);

    payment = new Payment();
    connect(this, SIGNAL(confirmation(QSqlTableModel*, QString, QString)), payment, SLOT(confirmation(QSqlTableModel*, QString, QString)));
    connect(payment, SIGNAL(backPayment(QString)), this, SLOT(backPayment(QString)));
    connect(payment, SIGNAL(cancelPayment()), this, SLOT(cancelPayment()));

    hideFriend();
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
    this->viewNotebookFriend();

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
    viewModel->setColumnCount(3);

    //QStringList headers = QStringList() << "user_id" << "price" << "card_number" << "datetime";
    QStringList headers = QStringList() << "Price" << "Номер карты" << "Дата";
    viewModel->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < rowCount; i++){
        QJsonObject operation = QJsonDocument().fromJson(model->record(i).value("json").toByteArray()).object();
        //viewModel->setItem(i, 0, new QStandardItem(operation["user_id"].toString()));
        viewModel->setItem(i, 0, new QStandardItem(operation["price"].toString()));
        viewModel->setItem(i, 1, new QStandardItem(operation["card_number"].toString()));
        viewModel->setItem(i, 2, new QStandardItem(operation["datetime"].toString()));
    }

    ui->tableView->setModel(viewModel);
}

void MainWindow::viewNotebookFriend(){
    DataBasePSQL* dbSingle = DataBasePSQL::Instance();
    QSqlDatabase db = dbSingle->getDB();
    QSqlQuery query(db);
    QSqlQuery querySel(db);
    viewNotebook = new QStandardItemModel();
    QString strFriend = QString("SELECT friend_id, friend_name FROM notebook WHERE user_id = '%1'").arg(userID);
    query.exec(strFriend);
    int count = 0;
    while (query.next()) {
        QString friend_id = query.value("friend_id").toString();
        QString friend_name = query.value("friend_name").toString();
        QString str = QString("SELECT phone FROM people WHERE user_id = '%1'").arg(friend_id);
        querySel.exec(str);
        querySel.next();
        QString friend_phone = querySel.value("phone").toString();
        viewNotebook->setItem(count, 0, new QStandardItem(friend_name + "\n" + friend_phone));
        viewNotebook->setItem(count, 1, new QStandardItem(friend_id));
        count++;
    }
     ui->listView->setModel(viewNotebook);
}

void MainWindow::on_payConfirm_clicked()
{
    this->hide();
    this->model->setTable("people");
    QString filter = QString("login='%1'").arg(this->Login);
    this->model->setFilter(filter);
    this->model->select();
    emit confirmation(this->model, userID, userID);
    payment->show();
}

void MainWindow::backPayment(QString newScore){
    if (newScore != "")
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

void MainWindow::on_okFriend_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(" ");
    bool isValid = true;
    int pos =  0 ;
    QString frend_phone = ui->friendPhone->text();
    QString frend_name = ui->friendName->text();
    QString err = "";

    if(name_validator->validate(frend_name, pos) != QValidator::Acceptable){
        isValid=false;
        err = "Некорректное имя";
    }
    if(phone_validator->validate(frend_phone, pos) != QValidator::Acceptable){
        isValid=false;
        if(err != ""){
            err = "Некорректные имя и телефон" ;
        }else{
            err = "Некорректный телефон" ;
        }
    }
    if(isValid){
        this->model->setTable("people");
        QString filter = QString("phone='%1'").arg(frend_phone);
        this->model->setFilter(filter);
        this->model->select();
        QString friendID;
        if(model->rowCount()>0){
            friendID = this->model->record(0).value("user_id").toString();
            if(friendID == userID){
                msgBox.setText("Нельзя добавить себя");
                msgBox.exec();
            }else{
                this->model->setTable("notebook");
                QSqlRecord newRecord = model->record();
                newRecord.setValue("user_id", userID);
                newRecord.setValue("friend_id", friendID);
                newRecord.setValue("friend_name", frend_name);
                model->insertRecord(-1,newRecord);
                hideFriend();
                this->viewNotebookFriend();
            }
            //model->submitAll();
        }else{
            msgBox.setText("Такого номера не существует");
            msgBox.exec();
        }
    }else{
        msgBox.setText(err);
        msgBox.exec();
    }

}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    this->hide();
    this->model->setTable("people");
    QString filter = QString("login='%1'").arg(this->Login);
    this->model->setFilter(filter);
    this->model->select();
    emit confirmation(this->model, userID, viewNotebook->item(index.row(),1)->text());
    payment->show();
}

void MainWindow::on_addFriend_clicked()
{
    showFriend();
}

void  MainWindow::showFriend(){
    ui->friendName->show();
    ui->friendPhone->show();
    ui->okFriend->show();
    ui->cancelFriend->show();
    ui->labelName->show();
    ui->labelPhone->show();
}

void  MainWindow::hideFriend(){
    ui->friendName->hide();
    ui->friendPhone->hide();
    ui->okFriend->hide();
    ui->cancelFriend->hide();
    ui->friendName->clear();
    ui->friendPhone->clear();
    ui->labelName->hide();
    ui->labelPhone->hide();
}

void MainWindow::on_cancelFriend_clicked()
{
    hideFriend();
}
