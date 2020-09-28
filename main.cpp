#include "mainwindow.h"
#include "activation.h"
#include "authentication.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Authentication w;
    w.show();
    return a.exec();
}
