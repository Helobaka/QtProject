#include "authentication.h"
#include "ui_authentication.h"
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QDebug>
#include <QTableView>

Authentication::Authentication(QWidget *parent):
        QWidget(parent),
        ui(new Ui::Authentication)
{
     ui->setupUi(this);
}

Authentication::~Authentication()
{
    delete ui;
}

void Authentication::on_BtnLogin_clicked()
{

    //ура
    QString fwe;
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5433);
    db.setDatabaseName("main");
    db.setUserName("postgres");
    db.setPassword("12347");
    if(!db.open()){
        qDebug() << db.lastError().text();
    }


    QSqlTableModel* model = new QSqlTableModel(this, db);
    model->setTable("temp");
    model->select();
    ui->tableView->setModel(model);
//    QTableView *view = new QTableView;
//    view->setModel(&model);
//    view->show();

    QString Login = "qwerty";
    QString Password = "1234";
    QMessageBox msgBox;

    if (Login == ui->TextLogin->text() && Password == ui->TextPassword->text())
    {
        msgBox.setText("Проходите");
    }
    else{
        msgBox.setText("Не правильный логин или пароль");
    }
    msgBox.exec();
    db.close();
}
