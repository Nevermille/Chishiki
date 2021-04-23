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

        bool operator==(const Character &other);
        bool operator!=(const Character &other);
        bool isNull(void);

        Character(void);

        int getId(void);
        void setId(int _id);

        QString getCharacter(void);
        void setCharacter(QString _character);

        QString getOnyomi(void);
        void setOnyomi(QString _onyomi);

        QString getKunyomi(void);
        void setKunyomi(QString _kunyomi);

        QString getMeaning(void);

        void setType(int _type);
        int getType(void);

        void setStrokes(int _strokes);
        int getStrokes(void);

    private:
        int id;
        QString character;
        QString onyomi;
        QString kunyomi;
        int type;
        int strokes;
};

#endif // CHARACTER_H
