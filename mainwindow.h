#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "payment.h"
#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QStandardItemModel>
#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void  setClient(TcpClient* client);

    TcpClient* client;
    int countT = 0;

signals:
    //void confirmation(QSqlTableModel *model);
    void confirmation(QSqlTableModel *, QString, QString);

    void sgnGetPeople(QJsonDocument);

    void sgnAddFriend(QJsonDocument);

private slots:
    void getLogin(QString Login);

    void on_payConfirm_clicked();

    void backPayment(QString newScore);

    void cancelPayment();

    void on_ExitButton_clicked();

    void on_okFriend_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_addFriend_clicked();

    void on_cancelFriend_clicked();

    void sltGetPeopleResult(QJsonObject);

    void sltAddFriendResult(QJsonObject);

private:
    Ui::MainWindow *ui;
    QString Login;
    QString userID;
    QSqlTableModel *model;
    Payment *payment;
    QStandardItemModel* viewModel;
    QStandardItemModel* viewNotebook;
    QRegExpValidator *phone_validator, *name_validator;

    void showFriend();
    void hideFriend();
    void viewOperations();
    void viewNotebookFriend();
};
#endif // MAINWINDOW_H
