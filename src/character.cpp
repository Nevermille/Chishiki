#include <QCoreApplication>
#include "include/character.h"

Character::Character(void)
{

}

QString* Character::getId(void)
{
    return id;
}

/**
 * @brief Character::getCharacter
 * @return The character
 */
QString* Character::getCharacter(void)
{
    return character;
}

QString* Character::getOnyomi(void)
{
    return onyomi;
}

QString* Character::getKunyomi(void)
{
    return kunyomi;
}

QList<CharacterTestResult>* Character::getResults(void)
{
    return results;
}

QString* Character::getMeaning(void)
{
    return new QString(tr(id->toStdString().c_str(), "character"));
}
