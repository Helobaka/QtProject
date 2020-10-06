#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "payment.h"
#include <QMainWindow>
#include <QSqlRelationalTableModel>

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

private:
    Ui::MainWindow *ui;
    QString Login;
    QSqlTableModel *model;
    Payment *payment;
};
#endif // MAINWINDOW_H
