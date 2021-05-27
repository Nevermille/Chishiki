#include "include/db/charset.h"

Charset::Charset()
{
    id = -1;
}

bool Charset::isNull(void) const
{
    if (id < 0)
    {
        return true;
    }

    return false;
}

bool Charset::operator==(const Charset &other) const
{
    if (id != other.id
            || name != other.name)
    {
        return false;
    }

    return true;
}

bool Charset::operator!=(const Charset &other) const
{
    if (id != other.id
            || name != other.name)
    {
        return true;
    }

    return false;
}

int Charset::getId(void) const
{
   return id;
}

void Charset::setId(int _id)
{
    id = _id;
}

QString Charset::getName(void) const
{
    return name;
}

void Charset::setName(QString _name)
{
    name = _name;
}
