#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap( QPixmap(":/images/splash.png") );

    splash->show();

    QThread::sleep( 2 );

    MainWindow w;
    w.show();


    splash->finish(&w);
    delete splash;

    return a.exec();
}
