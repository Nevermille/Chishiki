#ifndef KANJISELECTOR_H
#define KANJISELECTOR_H

#include <QWidget>
#include "include/db/charset.h"

namespace Ui {
class KanjiSelector;
}

class KanjiSelector : public QWidget
{
    Q_OBJECT

    public:
        explicit KanjiSelector(QWidget *parent = nullptr);
        void setCharsetList(QList<Charset> &list);
        ~KanjiSelector();

private slots:
        void on_charsetCombo_currentIndexChanged(int index);

private:
        Ui::KanjiSelector *ui;
        void fillCharacterTable(const Charset &charset);
};

#endif // KANJISELECTOR_H
