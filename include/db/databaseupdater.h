#ifndef DATABASEUPDATER_H
#define DATABASEUPDATER_H

#include <QJsonObject>

class DatabaseUpdater
{
    public:
        static void autoUpdate(void);

    private:
        static void createDatabase(void);
        static void buildDatabase(void);
        static bool isViableCharacterReference(const QJsonObject &ref);
};

#endif // DATABASEUPDATER_H
