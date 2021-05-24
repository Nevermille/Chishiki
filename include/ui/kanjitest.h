#ifndef KANJITEST_H
#define KANJITEST_H

#include <QWidget>

namespace Ui {
class KanjiTest;
}

class KanjiTest : public QWidget
{
    Q_OBJECT

public:
    explicit KanjiTest(QWidget *parent = nullptr);
    ~KanjiTest();

private:
    Ui::KanjiTest *ui;
};

#endif // KANJITEST_H
