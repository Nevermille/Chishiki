#ifndef CHARACTERCHOOSER_H
#define CHARACTERCHOOSER_H

#include <QWidget>
#include "include/widget/kanjiselector.h"

namespace Ui {
class CharacterChooser;
}

#define CHARACTERCHOOSER_CHARACTER_ROW 0
#define CHARACTERCHOOSER_MEANING_ROW 1
#define CHARACTERCHOOSER_ID_ROW 2

class CharacterChooser : public QWidget
{
    Q_OBJECT

    signals:
        void returnToHome(void);

    public:
        static const int KanjiTest = 1;
        static const int KanaTest = 2;
        static const int KanjiLearn = 3;
        static const int KanaLearn = 4;

        static const int AllCharsList = 0;
        static const int KanjiList = 1;
        static const int KanaList = 2;

        explicit CharacterChooser(QWidget *parent = nullptr);
        ~CharacterChooser();

        void setListMode(int mode);
        void setActionMode(int mode);
        void resetUi(void);

    private slots:
        void on_addOneCharButton_clicked();
        void on_kanjiSelector_charsetChanged();
        void on_addAllCharssButton_clicked();

        void on_removeOneCharButton_clicked();

        void on_removeAllCharsButton_clicked();

private:
        Ui::CharacterChooser *ui;
        int listMode;
        int actionMode;
        void addToSelectedList(const QList<Character> &characters);
        QList<Character> getChoosenCharacters(void);
};

#endif // CHARACTERCHOOSER_H
