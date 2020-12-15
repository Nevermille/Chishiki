#include "include/ui/mainwindow.h"
#include <QSplashScreen>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap splashBitmap(":/splash/images/splash/winter.png");
    QSplashScreen splash(splashBitmap);
    splash.show();
    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
