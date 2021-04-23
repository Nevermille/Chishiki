#include "include/etc/path.h"
#include <QStandardPaths>
#include <QDir>

/**
 * @brief Path::autoCreateDataPath Creates the data directory if it doesn't exist
 */
void Path::autoCreateDataPath(void)
{
    QString path = Path::getDataPath();

    if (!QDir(path).exists())
    {
        QDir().mkdir(path);
        qDebug() << "Directory" << path << "created";
    }
}

/**
 * @brief Path::getDataPath Returns the data directory
 * @return The data directory
 */
QString Path::getDataPath(void)
{
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + QDir::separator() + QString(".chishiki");
}

/**
 * @brief Path::getDbPath Returns the database location
 * @return The database location
 */
QString Path::getDbPath(void)
{
    return Path::getDataPath() + QDir::separator() + "userdata.db";
}
