#include <QCoreApplication>
#include "include/db/character.h"

Character::Character(void)
{
    id = -1;
    character = "";
    kunyomi = "";
    onyomi = "";
    type = -1;
    strokes = -1;
}

bool Character::operator==(const Character &other) const
{
    if (id != other.id
            || character != other.character
            || onyomi != other.onyomi
            || kunyomi != other.kunyomi
            || type != other.type
            || strokes != other.strokes)
    {
        return false;
    }

    return true;
}

bool Character::operator!=(const Character &other) const
{
    if (id != other.id
            || character != other.character
            || onyomi != other.onyomi
            || kunyomi != other.kunyomi
            || type != other.type
            || strokes != other.strokes)
    {
        return true;
    }

    return false;
}

bool Character::isNull(void) const
{
    if (id == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Character::getId(void) const
{
    return id;
}

QString Character::getCharacter(void) const
{
    return character;
}

QString Character::getOnyomi(void) const
{
    return onyomi;
}

QString Character::getKunyomi(void) const
{
    return kunyomi;
}

QString Character::getMeaning(void) const
{
    return "TODO";
}

int Character::getType(void) const
{
    return type;
}

int Character::getStrokes(void) const
{
    return strokes;
}

void Character::setId(int _id)
{
    id = _id;
}

void Character::setCharacter(QString _character)
{
    character = _character;
}

void Character::setKunyomi(QString _kunyomi)
{
    kunyomi = _kunyomi;
}

void Character::setOnyomi(QString _onyomi)
{
    onyomi = _onyomi;
}

void Character::setType(int _type)
{
    type = _type;
}

void Character::setStrokes(int _strokes)
{
    strokes = _strokes;
}
