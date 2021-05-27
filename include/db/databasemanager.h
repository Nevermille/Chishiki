#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QList>
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
        static void insertCharacter(const Character &character);
        static void updateCharacter(const Character &character);
        static void updateCharacter(int id, const Character &character);
        static void removeCharacter(const Character &character);
        static void removeCharacter(int id);

        // charset table management
        static Charset rowToCharset(const QSqlQuery &query);
        static Charset getCharset(int id);
        static QList<Charset> getCharsetRange(int start, int end);
        static void insertCharset(const Charset &charset);
        static void updateCharset(const Charset &charset);

        // charset_item table management
        static void linkCharsetToCharacter(const Charset &charset, const Character &character);
        static bool areCharsetAndCharacterLinked(const Charset &charset, const Character &character);
        static QList<Character> getAllCharactersForCharset(const Charset &charset);

        // test table management

        // setting table management
        static bool settingTableExists(void);
        static QString getParameter(const QString &name);

    private:
        static QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
