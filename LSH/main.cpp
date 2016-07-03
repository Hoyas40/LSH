#include "mainwindow.h"
#include <QApplication>

#include "clientdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    ClientDialog diag;
    //diag.show();
    return a.exec();
}
