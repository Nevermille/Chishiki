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
        void setCharsetList(const QList<Charset> &list);
        void hideSelectedCharacters(void);
        void hideCharacters(const QList<Character> &list);
        void unhideCharacters(const QList<Character> &list);
        void selectAllCharacters(void);
        void unselect(void);
        void allowMultipleSelects(bool val);
        QList<Character> getSelectedCharacters(void);

    signals:
        void charsetChanged(void);
        void characterSelected(void);

    private slots:
        void on_charsetCombo_currentIndexChanged(int index);
        void on_kanjiTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

        void on_kanjiTable_cellClicked(int row, int column);

private:
        Ui::KanjiSelector *ui;
        void fillCharacterTable(const Charset &charset);
        void clear();
};

#endif // KANJISELECTOR_H
