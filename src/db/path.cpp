#include "include/db/path.h"
#include <QCoreApplication>
#include <QDir>

QString Path::getDbPath(const QString &dbName)
{
    return ":/db/database/" + dbName + ".json";
}
