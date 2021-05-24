#ifndef KANJIVIEWER_H
#define KANJIVIEWER_H

#include <QWidget>

namespace Ui {
class KanjiViewer;
}

class KanjiViewer : public QWidget
{
    Q_OBJECT

public:
    explicit KanjiViewer(QWidget *parent = nullptr);
    ~KanjiViewer();

private:
    Ui::KanjiViewer *ui;
};

#endif // KANJIVIEWER_H
