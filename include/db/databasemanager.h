#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include "character.h"
#include "charset.h"

class DatabaseManager
{
    public:
        // Database management
        static void connect(void);
        static void beginTransaction(void);
        static void rollback(void);
        static void commit(void);

        // character table management
        static Character getCharacter(int id);
        static void insertCharacter(Character character);
        static void updateCharacter(Character character);
        static void updateCharacter(int id, Character character);
        static void removeCharacter(Character character);
        static void removeCharacter(int id);

        // charset table management
        static Charset getCharset(int id);
        static void insertCharset(Charset charset);
        static void updateCharset(Charset charset);

        // charset_item table management
        static void linkCharsetToCharacter(Charset charset, Character character);
        static bool areCharsetAndCharacterLinked(Charset charset, Character character);

        // test table management

        // setting table management
        static bool settingTableExists(void);
        static QString getParameter(QString name);

    private:
        static QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
