#include "include/ui/mainwindow.h"
#include <QSplashScreen>
#include <QApplication>
#include <QtGlobal>
#include <QFile>
#include <QFontDatabase>
#include "include/etc/path.h"
#include "include/db/databasemanager.h"
#include "include/db/databaseupdater.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Welcome to Chishiki!";
    MainWindow w;

    // Loads splash screen
    qDebug() << "Loading splash screen";
    QPixmap splashBitmap(":/splash/images/splash/winter.png");
    QSplashScreen splash(splashBitmap);
    splash.show();

    qDebug() << "Checking data directory";
    Path::autoCreateDataPath();

    try
    {
        qDebug() << "Connecting to database";
        DatabaseManager::connect();
        qDebug() << "Checking app updates";
        DatabaseUpdater::autoUpdate();
    }
    catch (QString e)
    {
        qCritical().noquote() << e;
        a.quit();
    }

    qDebug() << "Loading fonts";
    if(!QFontDatabase::addApplicationFont(":/fonts/KSO.ttf"))
    {
        qDebug() << "Unable to load KSO font";
    }

    qDebug() << "Applying style";
    QFile file(":/style/light.qss");
    file.open(QIODevice::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    a.setStyleSheet(stylesheet);

    // Loads app window
    w.show();
    splash.finish(&w);
    return a.exec();
}
