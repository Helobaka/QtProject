#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Authentication; }
QT_END_NAMESPACE

class Authentication :  public QWidget{
    Q_OBJECT

public:
    explicit Authentication(QWidget *parent=0);
    ~Authentication();

private slots:
    void on_BtnLogin_clicked();

private:
    Ui::Authentication *ui;
};


#endif // AUTHENTICATION_H
