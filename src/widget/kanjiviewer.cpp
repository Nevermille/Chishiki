#include "include/widget/kanjiviewer.h"
#include "ui_kanjiviewer.h"

KanjiViewer::KanjiViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanjiViewer)
{
    ui->setupUi(this);
    ui->kanji->setFont(QFont("KanjiStrokeOrders", 100));
}

KanjiViewer::~KanjiViewer()
{
    delete ui;
}

void KanjiViewer::printCharacter(const Character &character)
{
    ui->onyomiLabel->setText(character.getOnyomi().replace("・", "\n"));
    ui->kunyomiLabel->setText(character.getKunyomi().replace("・", "\n"));
    ui->meaningLabel->setText(character.getMeaning());
    ui->kanji->setText(character.getCharacter());
}
