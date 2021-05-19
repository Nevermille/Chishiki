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

    sql.prepare("SELECT * FROM \"character\" c WHERE id = ?");
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

    sql.prepare("INSERT INTO \"character\"(id, \"char\", onyomi, kunyomi, \"type\", strokes) VALUES(?, ?, ?, ?, ?, ?)");
    sql.addBindValue(character.getId());
    sql.addBindValue(character.getCharacter());
    sql.addBindValue(character.getOnyomi());
    sql.addBindValue(character.getKunyomi());
    sql.addBindValue(character.getType());
    sql.addBindValue(character.getStrokes());

    if (!sql.exec())
    {
        throw QString("Error during character insert");
    }
}

void DatabaseManager::updateCharacter(Character character)
{
    QSqlQuery sql;

    if (character.isNull())
    {
        throw QString("Character is null");
    }

    qDebug() << "Updating character" << character.getId();

    sql.prepare("UPDATE \"character\" SET \"char\"=?, onyomi=?, kunyomi=?, \"type\"=?, strokes=? WHERE id=?");
    sql.addBindValue(character.getCharacter());
    sql.addBindValue(character.getOnyomi());
    sql.addBindValue(character.getKunyomi());
    sql.addBindValue(character.getType());
    sql.addBindValue(character.getStrokes());
    sql.addBindValue(character.getId());

    if (!sql.exec())
    {
        throw QString("Error during character update");
    }
}

void DatabaseManager::insertCharset(Charset charset)
{
    QSqlQuery sql;

    if (charset.isNull())
    {
        throw QString("Charset is null");
    }

    qDebug() << "Inserting a charset";

    sql.prepare("INSERT INTO charset(id, name) VALUES(?, ?)");
    sql.addBindValue(charset.getId());
    sql.addBindValue(charset.getName());

    if (!sql.exec())
    {
        throw QString("Error during charset insert");
    }
}

void DatabaseManager::updateCharset(Charset charset)
{
    QSqlQuery sql;

    if (charset.isNull())
    {
        throw QString("Charset is null");
    }

    qDebug() << "Updating charset " << charset.getId();

    sql.prepare("UPDATE charset SET name=? WHERE id=?");
    sql.addBindValue(charset.getName());
    sql.addBindValue(charset.getId());

    if (!sql.exec())
    {
        throw QString("Error during charset update");
    }
}

Charset DatabaseManager::getCharset(int id)
{
    QSqlQuery sql;

    qDebug() << "Searching charset number" << id;

    sql.prepare("SELECT * FROM 'charset' c WHERE id = ?");
    sql.addBindValue(id);

    if (!sql.exec())
    {
        qWarning() << "Error during database query";
        return Charset();
    }

    if (sql.first())
    {
        Charset c;
        c.setId(sql.value(0).toInt());
        c.setName(sql.value(1).toString());

        return c;
    }
    else
    {
        return Charset();
    }
}

void DatabaseManager::linkCharsetToCharacter(Charset charset, Character character)
{
    QSqlQuery sql;

    if (charset.isNull())
    {
        throw QString("Charset is null");
    }

    if (character.isNull())
    {
        throw QString("Character is null");
    }

    qDebug() << "Inserting charset" << charset.getId() << "with character" << character.getId();

    sql.prepare("INSERT INTO charset_item(charset, \"character\") VALUES(?, ?)");
    sql.addBindValue(charset.getId());
    sql.addBindValue(character.getId());

    if (!sql.exec())
    {
        throw QString("Error during charset_item insert");
    }
}

bool DatabaseManager::areCharsetAndCharacterLinked(Charset charset, Character character)
{
    QSqlQuery sql;

    if (charset.isNull())
    {
        throw QString("Charset is null");
    }

    if (character.isNull())
    {
        throw QString("Character is null");
    }

    qDebug() << "Searching link between charset" << charset.getId() << "and character" << character.getId();

    sql.prepare("SELECT charset, \"character\" FROM charset_item WHERE charset=? AND \"character\"=?");
    sql.addBindValue(charset.getId());
    sql.addBindValue(character.getId());

    if (!sql.exec())
    {
        throw QString("Error during charset_item search");
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
