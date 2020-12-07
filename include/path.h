#ifndef PATH_H
#define PATH_H

#include <QString>

class Path
{
    public:
        static QString getDbPath(const QString &dbName);
};

#endif // PATH_H
