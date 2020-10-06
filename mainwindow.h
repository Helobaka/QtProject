#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "payment.h"
#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void confirmation(QSqlTableModel *model);

private slots:
    void getLogin(QString Login);

    void on_payConfirm_clicked();

    void backPayment(QString newScore);

    void cancelPayment();

    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;
    QString Login;
    QString userID;
    QSqlTableModel *model;
    Payment *payment;
    QStandardItemModel* viewModel;

    void viewOperations();
};
#endif // MAINWINDOW_H
