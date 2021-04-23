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

bool Character::operator==(const Character &other)
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

bool Character::operator!=(const Character &other)
{
    if (id == other.id
            && character == other.character
            && onyomi == other.onyomi
            && kunyomi == other.kunyomi
            && type == other.type
            && strokes == other.strokes)
    {
        return false;
    }

    return true;
}

bool Character::isNull(void)
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

int Character::getId(void)
{
    return id;
}

QString Character::getCharacter(void)
{
    return character;
}

QString Character::getOnyomi(void)
{
    return onyomi;
}

QString Character::getKunyomi(void)
{
    return kunyomi;
}

QString Character::getMeaning(void)
{
    return "TODO";
}

int Character::getType(void)
{
    return type;
}

int Character::getStrokes(void)
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
