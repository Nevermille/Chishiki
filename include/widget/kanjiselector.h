#ifndef KANJISELECTOR_H
#define KANJISELECTOR_H

#include <QWidget>
#include "include/db/charset.h"
#include "include/db/character.h"

namespace Ui {
class KanjiSelector;
}

#define KANJISELECTOR_CHARACTER_ROW 0
#define KANJISELECTOR_MEANING_ROW 1
#define KANJISELECTOR_ID_ROW 2

class KanjiSelector : public QWidget
{
    Q_OBJECT

    public:
        explicit KanjiSelector(QWidget *parent = nullptr);
        ~KanjiSelector();
        void setCharsetList(QList<Charset> &list);
        void hideSelectedCharacters(void);
        QList<Character> getSelectedCharacters(void);

    private slots:
        void on_charsetCombo_currentIndexChanged(int index);

    private:
        Ui::KanjiSelector *ui;
        void fillCharacterTable(const Charset &charset);
};

#endif // KANJISELECTOR_H
