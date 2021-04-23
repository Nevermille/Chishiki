#ifndef PATH_H
#define PATH_H

#include <QString>

class Path
{
    public:
        static void autoCreateDataPath(void);
        static QString getDbPath(void);
        static QString getDataPath(void);
};

#endif // PATH_H
