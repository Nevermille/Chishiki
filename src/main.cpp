#include "include/ui/mainwindow.h"
#include <QSplashScreen>
#include <QApplication>
#include <QtGlobal>
#include "include/etc/path.h"
#include "include/db/databasemanager.h"
#include "include/db/databaseupdater.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Welcome to Chishiki!";

    // Loads splash screen
    qDebug() << "Loading splash screen";
    QPixmap splashBitmap(":/splash/images/splash/winter.png");
    QSplashScreen splash(splashBitmap);
    splash.show();

    qDebug() << "Checking data directory";
    Path::autoCreateDataPath();

    try
    {
        DatabaseManager::connect();
        qDebug() << "Checking app updates";
        DatabaseUpdater::autoUpdate();
    }
    catch (QString e)
    {
        qCritical().noquote() << e;
        a.quit();
    }

    // Loads app window
    /*MainWindow w;
    w.show();
    splash.finish(&w);*/

    a.quit();
    return a.exec();
}
