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

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
