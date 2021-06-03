#ifndef KANJIVIEWER_H
#define KANJIVIEWER_H

#include <QWidget>
#include "include/db/character.h"

namespace Ui {
class KanjiViewer;
}

class KanjiViewer : public QWidget
{
    Q_OBJECT

public:
    explicit KanjiViewer(QWidget *parent = nullptr);
    ~KanjiViewer();
    void printCharacter(const Character &character);

private:
    Ui::KanjiViewer *ui;
};

#endif // KANJIVIEWER_H
