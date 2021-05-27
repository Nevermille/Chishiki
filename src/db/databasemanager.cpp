#include <QSqlDatabase>
#include <QSqlQuery>
#include "include/db/databasemanager.h"
#include "include/etc/path.h"

QSqlDatabase DatabaseManager::db;

void DatabaseManager::beginTransaction(void)
{
    qDebug() << "Begining trasaction";
    db.transaction();
}

void DatabaseManager::rollback(void)
{
    qDebug() << "Canceling DB changes";
    db.rollback();
}

void DatabaseManager::commit(void)
{
    qDebug() << "Applying DB changes";
    db.commit();
}

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

void DatabaseManager::insertCharacter(const Character &character)
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

void DatabaseManager::updateCharacter(const Character &character)
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

Charset DatabaseManager::rowToCharset(const QSqlQuery &query)
{
    Charset c;
    c.setId(query.value(0).toInt());
    c.setName(query.value(1).toString());

    return c;
}

void DatabaseManager::insertCharset(const Charset &charset)
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

void DatabaseManager::updateCharset(const Charset &charset)
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
        return rowToCharset(sql);
    }
    else
    {
        return Charset();
    }
}

QList<Charset> DatabaseManager::getCharsetRange(int start, int end)
{
    QSqlQuery sql;
    QList<Charset> result;

    qDebug() << "Searching charset between number" << start << "and" << end;

    sql.prepare("SELECT * FROM 'charset' c WHERE id BETWEEN ? and ?");
    sql.addBindValue(start);
    sql.addBindValue(end);

    if (!sql.exec())
    {
        qWarning() << "Error during database query";
        return QList<Charset>();
    }

    while (sql.next())
    {
        result.append(rowToCharset(sql));
    }

    return result;
}

void DatabaseManager::linkCharsetToCharacter(const Charset &charset, const Character &character)
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

bool DatabaseManager::areCharsetAndCharacterLinked(const Charset &charset, const Character &character)
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

QList<Character> DatabaseManager::getAllCharactersForCharset(const Charset &charset)
{
    QSqlQuery sql;
    QList<Character> result;

    if (charset.isNull())
    {
        throw QString("Charset is null");
    }

    qDebug() << "Getting all characters for charset" << charset.getId();

    sql.setForwardOnly(true);
    sql.prepare("SELECT charset, \"character\" FROM charset_item WHERE charset=?");
    sql.addBindValue(charset.getId());

    if (!sql.exec())
    {
        throw QString("Error during charset_item search");
    }

    while (sql.next())
    {
        result.append(getCharacter(sql.value(1).toInt()));
    }

    return result;
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

QString DatabaseManager::getParameter(const QString &name)
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
