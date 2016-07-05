#include "mainwindow.h"
#include <QApplication>

#include "operationdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();



//    OperationDialog diag;
//    diag.show();

    return a.exec();
}
