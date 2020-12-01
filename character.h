#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QList>
#include "charactertestresult.h"

class Character
{
    public:
        Character();
        QString getCharacter();
        QString getOnyomi();
        QString getKunyomi();
        QString getMeaning();
        QList<CharacterTestResult> getResults();

    private:
        QString id;
        QString character;
        QString onyomi;
        QString kunyomi;
        QString meaning;
        QList<CharacterTestResult> results;
};

#endif // CHARACTER_H
