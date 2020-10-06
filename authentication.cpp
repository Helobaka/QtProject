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
     mainWindow = new MainWindow();
     connect(this, SIGNAL(sendLogin(QString)), mainWindow, SLOT(getLogin(QString)));
}

Authentication::~Authentication()
{
    delete ui;
}

void Authentication::on_BtnLogin_clicked()
{
    QMessageBox msgBox;

    DataBasePSQL* dbSingle = DataBasePSQL::Instance();
    QSqlDatabase db = dbSingle->getDB();
    QSqlTableModel* model = new QSqlTableModel(this, db);

    model->setTable("people");
    QString filter = QString("login='%1'").arg(ui->TextLogin->text());
    model->setFilter(filter);
    model->select();

    if (model->rowCount() == 1){
        QString login = model->record(0).value("login").toString();
        QString password = model->record(0).value("password").toString();
        if (password == ui->TextPassword->text())
        {
            msgBox.setText("Проходите");
            mainWindow->show();
            emit sendLogin(login);
            this->close();
//            this->~Authentication();
        }
        else{
            msgBox.setText("Не правильный пароль");
        }
    }else {
       msgBox.setText("Такого логина нет");
    }

//    ui->tableView->setModel(model);


    msgBox.exec();
    db.close();
}

void Authentication::on_Registration_clicked()
{
    hide();
    registration = new Registration();
    connect(registration, SIGNAL(callBackRegistration()), this, SLOT(callBackRegistration()));
    registration->show();
}

void Authentication::callBackRegistration(){
    show();
}
