#include <QSqlDatabase>
#include <QSqlQuery>
#include "include/db/databasemanager.h"
#include "include/etc/path.h"

QSqlDatabase DatabaseManager::db;


void DatabaseManager::connect(void)
{
    qDebug() << "Checking driver availability";

    if (!QSqlDatabase::isDriverAvailable("QSQLITE"))
    {
        throw QString("Database driver not available");
    }

    qDebug().noquote() << "Loading database at location" << Path::getDbPath();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Path::getDbPath());

    if (!db.open())
    {
        throw QString("Unable to open database");
    }
}

Character DatabaseManager::getCharacter(int id)
{
    QSqlQuery sql;

    qDebug() << "Searching character number" << id;

    sql.prepare("SELECT * FROM 'character' c WHERE id = ?");
    sql.addBindValue(id);

    if (!sql.exec())
    {
        qWarning() << "Error during database query";
        return Character();
    }

    if (sql.first())
    {
        Character c;
        c.setId(sql.value(0).toInt());
        c.setCharacter(sql.value(1).toString());
        c.setOnyomi(sql.value(2).toString());
        c.setKunyomi(sql.value(3).toString());
        c.setType(sql.value(4).toInt());
        c.setStrokes(sql.value(5).toInt());

        return c;
    }
    else
    {
        return Character();
    }
}

void DatabaseManager::insertCharacter(Character character)
{
    QSqlQuery sql;

    if (character.isNull())
    {
        throw QString("Character is null");
    }

    qDebug() << "Inserting a character";

    sql.prepare("INSERT INTO 'character'(id, 'char', onyomi, kunyomi, 'type', strokes) VALUES(?, ?, ?, ?, ?, ?)");
    sql.addBindValue(character.getId());
    sql.addBindValue(character.getCharacter());
    sql.addBindValue(character.getOnyomi());
    sql.addBindValue(character.getKunyomi());
    sql.addBindValue(character.getType());
    sql.addBindValue(character.getStrokes());

    if (!sql.exec())
    {
        qWarning() << "Error during character insert";
    }
}

bool DatabaseManager::settingTableExists(void)
{
    QSqlQuery sql;

    sql.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name='setting'");

    qDebug() << "Checking setting table";

    if (!sql.exec())
    {
        throw QString("Error during database query");
    }

    if (sql.first())
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString DatabaseManager::getParameter(QString name)
{
    QSqlQuery sql;

    sql.prepare("SELECT value FROM setting where name = ?");
    sql.addBindValue(name);

    qDebug() << "Getting setting" << name;

    if (!sql.exec())
    {
        throw QString("Error during database query");
    }

    if (sql.first())
    {
        return sql.value(0).toString();
    }
    else
    {
        return nullptr;
    }
}
