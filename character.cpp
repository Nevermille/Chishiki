#include "character.h"

Character::Character()
{

}

/**
 * @brief Character::getCharacter
 * @return The character
 */
QString Character::getCharacter()
{
    return character;
}

QString Character::getMeaning()
{
    return meaning;
}

QString Character::getOnyomi()
{
    return onyomi;
}

QString Character::getKunyomi()
{
    return kunyomi;
}

QList<CharacterTestResult> Character::getResults()
{
    return results;
}
