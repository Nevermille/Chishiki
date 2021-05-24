#ifndef KANJISELECTOR_H
#define KANJISELECTOR_H

#include <QWidget>

namespace Ui {
class KanjiSelector;
}

class KanjiSelector : public QWidget
{
    Q_OBJECT

public:
    explicit KanjiSelector(QWidget *parent = nullptr);
    ~KanjiSelector();

private:
    Ui::KanjiSelector *ui;
};

#endif // KANJISELECTOR_H
