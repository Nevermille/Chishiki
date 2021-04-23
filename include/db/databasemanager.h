#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include "character.h"

class DatabaseManager
{
    public:
        // Database management
        static void connect(void);

        // character table management
        static Character getCharacter(int id);
        static void insertCharacter(Character character);
        static void updateCharacter(Character character);
        static void updateCharacter(int id, Character character);
        static void removeCharacter(Character character);
        static void removeCharacter(int id);

        // test table management

        // setting table management
        static bool settingTableExists(void);
        static QString getParameter(QString name);

    private:
        static QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
