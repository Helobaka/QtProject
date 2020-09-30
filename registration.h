#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Registration; }
QT_END_NAMESPACE

class Registration:  public QWidget{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent=0);
    ~Registration();

signals:
    void callBack();

private slots:
    void on_callBack_clicked();

    void on_register_2_clicked();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
