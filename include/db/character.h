#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QList>
#include <QCoreApplication>
#include "charactertestresult.h"

class Character
{
    Q_DECLARE_TR_FUNCTIONS(Character)

    public:
        Character(void);
        QString* getId(void);
        QString* getCharacter(void);
        QString* getOnyomi(void);
        QString* getKunyomi(void);
        QString* getMeaning(void);
        QList<CharacterTestResult>* getResults(void);

    private:
        QString* id;
        QString* character;
        QString* onyomi;
        QString* kunyomi;
        QString* meaning;
        QList<CharacterTestResult>* results;
};

#endif // CHARACTER_H
