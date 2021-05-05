#ifndef DATABASEUPDATER_H
#define DATABASEUPDATER_H

#include <QJsonObject>
#include <QCoreApplication>

class DatabaseUpdater
{
    Q_DECLARE_TR_FUNCTIONS(DatabaseUpdater);

    public:
        static void autoUpdate(void);

    private:
        static void createDatabase(void);
        static void buildDatabase(void);
        static void buildCharacterDatabase(void);
        static void buildCharsetDatabase(void);
        static bool isViableCharacterReference(const QJsonObject &ref);
        static bool isViableCharsetReference(const QJsonObject &ref);
};

#endif // DATABASEUPDATER_H
