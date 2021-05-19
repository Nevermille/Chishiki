#include <QSqlQuery>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QProgressDialog>
#include "include/db/databaseupdater.h"
#include "include/db/databasemanager.h"
#include "include/etc/chishiki.h"
#include "include/db/character.h"

void DatabaseUpdater::autoUpdate(void)
{
    if (!DatabaseManager::settingTableExists())
    {
        createDatabase();
        buildDatabase();
    }

    if (DatabaseManager::getParameter("app.version") != CHISHIKI_VERSION)
    {
        buildDatabase();
    }
}

void DatabaseUpdater::createDatabase(void)
{
    QSqlQuery sql;

    qDebug() << "Creating character table";
    sql.prepare("CREATE TABLE 'character' (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 'char' TEXT NOT NULL, onyomi TEXT, kunyomi TEXT, 'type' INTEGER NOT NULL, strokes INTEGER NOT NULL)");

    if (!sql.exec())
    {
        throw QString("Error during character table creation");
    }

    qDebug() << "Creating test table";
    sql.prepare("CREATE TABLE test (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, date TEXT NOT NULL, done INTEGER, 'type' INTEGER NOT NULL);");

    if (!sql.exec())
    {
        throw QString("Error during test table creation");
    }

    qDebug() << "Creating test_item table";
    sql.prepare("CREATE TABLE test_item (test INTEGER NOT NULL, 'number' INTEGER NOT NULL, 'character' INTEGER NOT NULL, 'result' INTEGER DEFAULT 0 NOT NULL);");

    if (!sql.exec())
    {
        throw QString("Error during test_item table creation");
    }

    qDebug() << "Creating test_item index";
    sql.prepare("CREATE UNIQUE INDEX test_item_test_IDX ON test_item (test,'number')");

    if (!sql.exec())
    {
        throw QString("Error during test_item item creation");
    }

    qDebug() << "Creating charset table";
    sql.prepare("CREATE TABLE charset (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL);");

    if (!sql.exec())
    {
        throw QString("Error during charset table creation");
    }

    qDebug() << "Creating charset_item table";
    sql.prepare("CREATE TABLE charset_item (charset INTEGER NOT NULL, 'character' INTEGER NOT NULL)");

    if (!sql.exec())
    {
        throw QString("Error during charset_item table creation");
    }

    qDebug() << "Creating charset_item index";
    sql.prepare("CREATE UNIQUE INDEX charset_item_charset_IDX ON charset_item (charset,'character')");

    if (!sql.exec())
    {
        throw QString("Error during charset_item index creation");
    }

    qDebug() << "Creating setting table";
    sql.prepare("CREATE TABLE 'setting' (name TEXT NOT NULL, value TEXT NOT NULL)");

    if (!sql.exec())
    {
        throw QString("Error during setting table creation");
    }

    sql.prepare("INSERT INTO setting(name, value) VALUES('app.version', ?)");
    sql.addBindValue(CHISHIKI_VERSION);

    if (!sql.exec())
    {
        throw QString("Error during app version insert query");
    }
}

void DatabaseUpdater::buildDatabase(void)
{
    buildCharacterDatabase();
    buildCharsetDatabase();
}

void DatabaseUpdater::buildCharacterDatabase(void)
{
    qDebug() << "Updating character database";
    QFile characterFile(":/database/character.json");

    qDebug() << "Opening character database reference";
    if (!characterFile.open(QIODevice::ReadOnly))
    {
        throw QString("Unable to open character database reference");
    }

    qDebug() << "Parsing JSON";
    QJsonDocument characterReference = QJsonDocument::fromJson(characterFile.readAll());

    if (!characterReference.isArray())
    {
        throw QString("Character database reference corrupted");
    }

    QJsonArray characterList = characterReference.array();
    int total = characterList.count();
    int i = 0;
    QProgressDialog progress(tr("Building character database"), tr("Hide"), 0, total);
    progress.setModal(true);

    qDebug() << "Parsing array";
    for (i = 0; (i < total); i++)
    {
        QJsonValue characterItem = characterList.at(i);

        progress.setValue(i);
        progress.setLabelText(tr("Building character database") + " [" + QString::number(i) + "/" + QString::number(total) + "]");
        QCoreApplication::processEvents();

        if (!characterItem.isObject()) {
            qWarning() << "Character item corrupted";
            continue;
        }

        QJsonObject characterObject = characterItem.toObject();

        if (!isViableCharacterReference(characterObject))
        {
            qWarning() << "Character item corrupted";
            continue;
        }

        Character c;
        c.setId(characterObject["id"].toInt());
        c.setCharacter(characterObject["char"].toString());
        c.setKunyomi(characterObject["kunyomi"].toString());
        c.setOnyomi(characterObject["onyomi"].toString());
        c.setType(characterObject["type"].toInt());
        c.setStrokes(characterObject["strokes"].toInt());

        qDebug() << "Checking character" << c.getCharacter();

        Character baseCharacter = DatabaseManager::getCharacter(c.getId());

        if (baseCharacter.isNull())
        {
            DatabaseManager::insertCharacter(c);
        }
        else if (c != baseCharacter)
        {
            DatabaseManager::updateCharacter(c);
        }
    }

    progress.close();
}

void DatabaseUpdater::buildCharsetDatabase(void)
{
    qDebug() << "Updating charset database";
    QFile charsetFile(":/database/charset.json");

    qDebug() << "Opening charset database reference";
    if (!charsetFile.open(QIODevice::ReadOnly))
    {
        throw QString("Unable to open charset database reference");
    }

    qDebug("Parsing JSON");
    QJsonDocument charsetReference = QJsonDocument::fromJson(charsetFile.readAll());

    if (!charsetReference.isArray())
    {
        throw QString("Charset database reference corrupted");
    }

    QJsonArray charsetList = charsetReference.array();
    int total = charsetList.count();
    int i = 0;

    qDebug() << "Parsing array";
    for (i = 0; (i < total); i++)
    {
        QJsonValue charsetItem = charsetList.at(i);

        if (!charsetItem.isObject())
        {
            qWarning() << "Charset item corrumpted";
            continue;
        }

        QJsonObject charsetObject = charsetItem.toObject();

        if (!isViableCharsetReference(charsetObject))
        {
            qWarning() << "Charset item corrumpted";
            continue;
        }

        Charset chrset;
        chrset.setId(charsetObject["id"].toInt());
        chrset.setName(charsetObject["name"].toString());

        qDebug() << "Checking charset" << chrset.getName();

        Charset baseCharset = DatabaseManager::getCharset(chrset.getId());

        if (baseCharset.isNull())
        {
            DatabaseManager::insertCharset(chrset);
        }
        else if (chrset != baseCharset)
        {
            DatabaseManager::updateCharset(chrset);
        }

        QJsonArray charactersList = charsetObject["chars"].toArray();
        int totalChars = charactersList.count();
        int j = 0;

        qDebug() << "Checking character list";
        for (j = 0; (j < totalChars); j++)
        {
            QJsonValue charValue = charactersList.at(j);

            if (!charValue.isDouble())
            {
                qWarning() << "Character id is not a number";
                continue;
            }

            int charId = charValue.toInt();

            Character chr = DatabaseManager::getCharacter(charId);

            if (chr.isNull())
            {
                qWarning() << "Character id not found in database";
                continue;
            }

            if (!DatabaseManager::areCharsetAndCharacterLinked(chrset, chr))
            {
                DatabaseManager::linkCharsetToCharacter(chrset, chr);
            }
        }
    }
}

/*!
 * \brief DatabaseUpdater::isViableCharacterReference Checks if a character reference is in the right format
 * \param ref The reference object to test
 * \return true is good, false otherwise
 */
bool DatabaseUpdater::isViableCharacterReference(const QJsonObject &ref)
{
    if (!ref.contains("id"))
    {
        qWarning() << "Property id not found";
        return false;
    }

    if (!ref["id"].isDouble())
    {
        qWarning() << "Property id isn't a number";
        return false;
    }

    if (!ref.contains("char"))
    {
        qWarning() << "Property char not found";
        return false;
    }

    if (!ref["char"].isString())
    {
        qWarning() << "Property char isn't a string";
        return false;
    }

    if (!ref.contains("kunyomi"))
    {
        qWarning() << "Property kunyomi not found";
        return false;
    }

    if (!ref["kunyomi"].isString())
    {
        qWarning() << "Property kunyomi isn't a string";
        return false;
    }

    if (!ref.contains("onyomi"))
    {
        qWarning() << "Property onyomi not found";
        return false;
    }

    if (!ref["onyomi"].isString())
    {
        qWarning() << "Property onyomi isn't a string";
        return false;
    }

    if (!ref.contains("type"))
    {
        qWarning() << "Property type not found";
        return false;
    }

    if (!ref["type"].isDouble())
    {
        qWarning() << "Property type isn't a number";
        return false;
    }

    if (!ref.contains("strokes"))
    {
        qWarning() << "Property strokes not found";
        return false;
    }

    if (!ref["strokes"].isDouble())
    {
        qWarning() << "Property strokes isn't a number";
        return false;
    }

    return true;
}

bool DatabaseUpdater::isViableCharsetReference(const QJsonObject &ref)
{
    if (!ref.contains("id"))
    {
        qWarning() << "Property id not found";
        return false;
    }

    if (!ref["id"].isDouble())
    {
        qWarning() << "Property id is not a number";
        return false;
    }

    if (!ref.contains("name"))
    {
        qWarning() << "Property name not found";
        return false;
    }

    if (!ref["name"].isString())
    {
        qWarning() << "Property name is not a string";
        return false;
    }

    if (!ref.contains("chars"))
    {
        qWarning() << "Property chars not found";
        return false;
    }

    if (!ref["chars"].isArray())
    {
        qWarning() << "Property chars is not an array";
        return false;
    }

    return true;
}
