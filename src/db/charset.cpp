#include "include/db/charset.h"

Charset::Charset()
{
    id = -1;
}

bool Charset::isNull(void)
{
    if (id < 0)
    {
        return true;
    }

    return false;
}

bool Charset::operator==(const Charset &other)
{
    if (id != other.id
            || name != other.name)
    {
        return false;
    }

    return true;
}

bool Charset::operator!=(const Charset &other)
{
    if (id != other.id
            || name != other.name)
    {
        return true;
    }

    return false;
}

int Charset::getId(void)
{
   return id;
}

void Charset::setId(int _id)
{
    id = _id;
}

QString Charset::getName(void)
{
    return name;
}

void Charset::setName(QString _name)
{
    name = _name;
}
