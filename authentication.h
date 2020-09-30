#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "mainwindow.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Authentication; }
QT_END_NAMESPACE

class Authentication :  public QWidget{
    Q_OBJECT

public:
    explicit Authentication(QWidget *parent=0);
    ~Authentication();

signals:
    void sendLogin(QString Login);

private slots:
    void on_BtnLogin_clicked();

    void on_Registration_clicked();

private:
    Ui::Authentication *ui;
    MainWindow *mainWindow;
};


#endif // AUTHENTICATION_H
