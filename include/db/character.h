#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QList>
#include <QCoreApplication>

class Character
{
    Q_DECLARE_TR_FUNCTIONS(Character)

    public:
        static const int Kanji = 1;
        static const int Kana = 2;

        bool operator==(const Character &other) const;
        bool operator!=(const Character &other) const;
        bool isNull(void) const;

        Character(void);

        int getId(void) const;
        void setId(int _id);

        QString getCharacter(void) const;
        void setCharacter(QString _character);

        QString getOnyomi(void) const;
        void setOnyomi(QString _onyomi);

        QString getKunyomi(void) const;
        void setKunyomi(QString _kunyomi);

        QString getMeaning(void) const;

        void setType(int _type);
        int getType(void) const;

        void setStrokes(int _strokes);
        int getStrokes(void) const;

    private:
        int id;
        QString character;
        QString onyomi;
        QString kunyomi;
        int type;
        int strokes;
};

#endif // CHARACTER_H
